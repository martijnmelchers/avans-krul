#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>

#include "IOperation.h"
#include "OperationFactory.h"
#include "Krul.h"

#include "CurlWrapper.h"


namespace krul
{
    bool is_found = false;

    size_t write_function(void* ptr, size_t size, size_t nmemb, std::string* data) {
        data->append((char*)ptr, size * nmemb);
        return size * nmemb;
    }

	void read_labels(std::vector<std::string>& raw, operations::execute_data& data)
    {
        operation_factory factory = operation_factory();

	   for (std::string& i : raw)
        {
            if (i[0] == ':')
            {
                data.line = i;
                operations::base* op = factory.get_operation(data.line);

                op->execute(data);
            }
            data.position++;

        }

       data.position = 0;
    }
	
    std::string interpret(const std::string& input_string)
    {
        operation_factory factory = operation_factory();
        std::stringstream string_stream(input_string);
        std::string read_line;


    	// Data passed to operators
        std::vector<std::string> stack;
        std::map<std::string, std::string> variables;
        std::map<std::string, int> labels;
        std::vector<int> functions;
        int position = 0;
        std::string line;

        operations::execute_data data = operations::execute_data(stack, variables, labels, functions, position);


        // Read the data into a vector
        std::vector<std::string> raw_data;
        while (std::getline(string_stream, read_line, '\n'))
	        raw_data.push_back(read_line);

    	// Read labels first so they can be referenced
        read_labels(raw_data, data);

    	// Loop until end has been reached
        while (position < raw_data.size())
        {
            try
            {
                data.line = raw_data[position];
                operations::base* op = factory.get_operation(data.line);

                if (op != nullptr)
                    op->execute(data);

                if (data.line == "end")
                    is_found = true;

            }
        	catch(std::exception e)
            {
                std::cout << "An error occurred!" << std::endl;
            }

            position++;
        }

        return data.stack.back();

    }

    std::string request_url(const std::string& endpoint)
    {
	    const curl_wrapper wrapper = curl_wrapper(curl_easy_init());
        CURL* req = wrapper.get();
        std::string response;

        const std::string url = "https://www.swiftcoder.nl/cpp1/" + endpoint;

        if (req)
        {
            curl_easy_setopt(req, CURLOPT_URL, url.c_str());
            curl_easy_setopt(req, CURLOPT_FOLLOWLOCATION, 1L);

            curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, write_function);
            curl_easy_setopt(req, CURLOPT_WRITEDATA, &response);


            const CURLcode res = curl_easy_perform(req);
            if (res != CURLE_OK)
                fprintf(stderr, "curl_easy_operation() failed : %s\n", curl_easy_strerror(res));
        }

        return response;
    }

    void start_search(const std::string& url)
    {
        const std::string result = interpret(request_url(url));

        if (is_found)
        {
            std::cout << "Solution has been found!" << std::endl;
            std::cout << result << std::endl;
        }
        else
        {
            std::cout << "New URL found!" << std::endl;
            std::cout << result << std::endl;

            start_search(result);
        }
    }
}




