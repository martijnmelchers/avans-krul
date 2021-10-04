#pragma once
#include <map>
#include <string>
#include <vector>


namespace operations
{
	struct execute_data
	{
		execute_data(std::vector<std::string>& _s, std::map<std::string, std::string>& _v, std::map<std::string, int>& _l, std::vector<int>& _f, int& _p):
			stack(_s),
			variables(_v),
			labels(_l),
			functions(_f),
			position(_p)
		{
		}

		std::vector<std::string>& stack;
		std::map<std::string, std::string>& variables;
		std::map<std::string, int>& labels;
		std::vector<int>& functions;
		int& position;
		std::string line;
	};

	
	class base
	{
	public:
		virtual void execute(execute_data data) = 0;
	};


	class string : public base
	{
		void execute(execute_data data) override;
	};

	class integer : public base
	{
		void execute(execute_data data) override;
	};

	class variable : public base
	{
		void execute(execute_data data) override;
	};
	
	class variable_read : public base
	{
		void execute(execute_data data) override;
	};

	class label : public base
	{
		void execute(execute_data data) override;
	};

	class label_read : public base
	{
		void execute(execute_data data) override;
	};

	// String operations
	class duplicate : public base
	{
		void execute(execute_data data) override;
	};

	class reverse : public base
	{
		void execute(execute_data data) override;
	};

	class index : public base
	{
		void execute(execute_data data) override;
	};
	
	class concat : public base
	{
		void execute(execute_data data) override;
	};

	class length : public base
	{
		void execute(execute_data data) override;
	};

	class slice : public base
	{
		void execute(execute_data data) override;
	};

	class rotate : public base
	{
		void execute(execute_data data) override;
	};

	// Integer operations
	class add : public base
	{
		void execute(execute_data data) override;
	};

	class subtract : public base
	{
		void execute(execute_data data) override;
	};

	class increment : public base
	{
		void execute(execute_data data) override;
	};
	
	class decrement : public base
	{
		void execute(execute_data data) override;
	};

	class negate : public base
	{
		void execute(execute_data data) override;
	};

	class multiply : public base
	{
		void execute(execute_data data) override;
	};

	class divide : public base
	{
		void execute(execute_data data) override;
	};

	class modulo : public base
	{
		void execute(execute_data data) override;
	};

	class absolute : public base
	{
		void execute(execute_data data) override;
	};

	// Test & Jump operations
	class go_to : public base
	{
		void execute(execute_data data) override;
	};
	
	class goto_not_equal : public base
	{
		void execute(execute_data data) override;
	};

	class goto_less : public base
	{
		void execute(execute_data data) override;
	};

	class goto_less_equal : public base
	{
		void execute(execute_data data) override;
	};

	class goto_greater : public base
	{
		void execute(execute_data data) override;
	};


	class goto_greater_equal : public base
	{
		void execute(execute_data data) override;
	};

	// Functions
	class function : public base
	{
		void execute(execute_data data) override;
	};

	class function_return : public base
	{
		void execute(execute_data data) override;
	};

	// Other
	class new_line : public base
	{
		void execute(execute_data data) override;
	};

	class end : public base
	{
		void execute(execute_data data) override;
	};
	

}
