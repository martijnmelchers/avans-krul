#include <algorithm>
#include <string>
#include <iostream>

#include "./IOperation.h"



namespace operations
{
	std::string rot13(std::string a)
	{
		const int z = a.length();
		int i = 0;
		for (i = 0; i <= (z); i++)
		{
			if (a[i] < 91 && a[i] > 64)  
			{
				if (a[i] < 78)
					a[i] = a[i] + 13;
				else
					a[i] = a[i] - 13;
			}
			if (a[i] < 123 && a[i] > 96)
			{
				if (a[i] < 110)
					a[i] = a[i] + 13;
				else
					a[i] = a[i] - 13;
			}
		}
		return a;                                                              
	}
	
	std::string prepare_string(std::string input)
	{
		return input.erase(0, 1);
	}

	std::string get_and_pop(std::vector<std::string>& stack)
	{
		std::string value = stack.back();
		stack.pop_back();

		return value;
	}

	// String operation
	void string::execute(execute_data data)
	{
		data.stack.push_back(prepare_string(data.line));
	}

	// Integer operation
	void integer::execute(execute_data data)
	{
		data.stack.push_back(data.line);
	}


	// Variable operation
	void variable::execute(execute_data data)
	{
		const std::string content = get_and_pop(data.stack);
		data.variables[prepare_string(data.line)] = content;
	}

	void variable_read::execute(execute_data data)
	{
		data.stack.push_back(data.variables[prepare_string(data.line)]);
	}


	// Label operation
	void label::execute(execute_data data)
	{
		data.labels[prepare_string(data.line)] = data.position;
	}

	void label_read::execute(execute_data data)
	{
		data.stack.push_back(
			std::to_string(
				data.labels[prepare_string(data.line)]
			)
		);
	}

	// String operations
	void duplicate::execute(execute_data data)
	{
		data.stack.push_back(data.stack.back());
	}

	void reverse::execute(execute_data data)
	{
		std::string str = get_and_pop(data.stack);

		std::reverse(str.begin(), str.end());
		data.stack.push_back(str);
	}

	void index::execute(execute_data data)
	{
		const int index = std::stoi(get_and_pop(data.stack));
		std::string str = get_and_pop(data.stack);

		std::string indexedStr;
		indexedStr.push_back(str[index]);

		data.stack.push_back(indexedStr);
	}

	
	void concat::execute(execute_data data)
	{
		const std::string part1 = get_and_pop(data.stack);
		const std::string part2 = get_and_pop(data.stack);

		data.stack.push_back(part2 + part1);
	}

	void length::execute(execute_data data)
	{
		const std::string str = get_and_pop(data.stack);
		data.stack.push_back(std::to_string(str.length()));
	}

	void slice::execute(execute_data data)
	{
		const int to_index = std::stoi(get_and_pop(data.stack));
		const int from_index = std::stoi(get_and_pop(data.stack));

		const std::string value = get_and_pop(data.stack);

		const std::string new_value = value.substr(from_index, to_index - from_index);

		data.stack.push_back(new_value);
	}

	void rotate::execute(execute_data data)
	{
		const std::string rotated = rot13(get_and_pop(data.stack));
		data.stack.push_back(rotated);
	}



	// Integer operations
	void add::execute(execute_data data)
	{
		const int val1 = std::stoi(get_and_pop(data.stack));
		const int val2 = std::stoi(get_and_pop(data.stack));

		const std::string result = std::to_string((val2 + val1));
		data.stack.push_back(result);
	}

	void subtract::execute(execute_data data)
	{
		const int val1 = std::stoi(get_and_pop(data.stack));
		const int val2 = std::stoi(get_and_pop(data.stack));

		const std::string result = std::to_string((val2 - val1));
		data.stack.push_back(result);
	}
	
	void increment::execute(execute_data data)
	{
		int number = std::stoi(get_and_pop(data.stack));
		number++;

		data.stack.push_back(std::to_string(number));
	}

	
	void decrement::execute(execute_data data)
	{
		int number = std::stoi(get_and_pop(data.stack));
		number--;

		data.stack.push_back(std::to_string(number));
	}

	void negate::execute(execute_data data)
	{
		const int value = std::stoi(get_and_pop(data.stack));

		const std::string result = std::to_string(value * -1);
		data.stack.push_back(result);
	}


	void multiply::execute(execute_data data)
	{
		const int val1 = std::stoi(get_and_pop(data.stack));
		const int val2 = std::stoi(get_and_pop(data.stack));

		const std::string result = std::to_string((val2 * val1));
		data.stack.push_back(result);
	}


	void divide::execute(execute_data data)
	{
		const int val1 = std::stoi(get_and_pop(data.stack));
		const int val2 = std::stoi(get_and_pop(data.stack));

		const std::string result = std::to_string((val2 / val1));
		data.stack.push_back(result);
	}



	void modulo::execute(execute_data data)
	{
		const int val1 = std::stoi(get_and_pop(data.stack));
		const int val2 = std::stoi(get_and_pop(data.stack));

		const std::string result = std::to_string((val2 % val1));
		data.stack.push_back(result);
	}

	void absolute::execute(execute_data data)
	{
		const int value = std::stoi(get_and_pop(data.stack));

		const std::string result = std::to_string(std::abs(value));
		data.stack.push_back(result);
	}




	// Test & Jumps operations

	void go_to::execute(execute_data data)
	{
		data.position = std::stoi(get_and_pop(data.stack));
	}

	
	void goto_not_equal::execute(execute_data data)
	{
		const int goto_line = std::stoi(get_and_pop(data.stack));
		const std::string val1 = get_and_pop(data.stack);
		const std::string val2 = get_and_pop(data.stack);


		if (val2 != val1)
			data.position = goto_line;
	}

	void goto_less::execute(execute_data data)
	{
		const int goto_line = std::stoi(get_and_pop(data.stack));
		const int val1 = std::stoi(get_and_pop(data.stack));
		const int val2 = std::stoi(get_and_pop(data.stack));


		if (val2 < val1)
			data.position = goto_line;
	}

	void goto_less_equal::execute(execute_data data)
	{
		const int goto_line = std::stoi(get_and_pop(data.stack));
		const int val1 = std::stoi(get_and_pop(data.stack));
		const int val2 = std::stoi(get_and_pop(data.stack));


		if (val2 <= val1)
			data.position = goto_line;
	}

	void goto_greater::execute(execute_data data)
	{
		const int goto_line = std::stoi(get_and_pop(data.stack));
		const int val1 = std::stoi(get_and_pop(data.stack));
		const int val2 = std::stoi(get_and_pop(data.stack));

		if (val2 > val1)
			data.position = goto_line;
	}


	void goto_greater_equal::execute(execute_data data)
	{
		const int goto_line = std::stoi(get_and_pop(data.stack));
		const int val1 = std::stoi(get_and_pop(data.stack));
		const int val2 = std::stoi(get_and_pop(data.stack));

		if (val2 >= val1)
			data.position = goto_line;
	}


	

	// Functions and other
	void function::execute(execute_data data)
	{
		data.functions.push_back(data.position);

		data.position = std::stoi(data.stack.back());
		data.stack.pop_back();		
	}

	void function_return::execute(execute_data data)
	{
		const int line = data.functions.back();
		data.functions.pop_back();

		data.position = line;
	}


	void new_line::execute(execute_data data)
	{
		std::string line = get_and_pop(data.stack);
		line.append("\n");

		data.stack.push_back(line);
	}

	void end::execute(execute_data data)
	{
		
	}











};
