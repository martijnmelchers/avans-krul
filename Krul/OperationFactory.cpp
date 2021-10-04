#include "OperationFactory.h"
#include <iostream>


bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

operation_factory::operation_factory()
{
	operators_.insert(
		std::pair<std::string, operations::add*>("add", new operations::add())
	);
	operators_.insert(
		std::pair<std::string, operations::subtract*>("sub", new operations::subtract())
	);
	operators_.insert(
		std::pair<std::string, operations::multiply*>("mul", new operations::multiply())
	);
	operators_.insert(
		std::pair<std::string, operations::divide*>("div", new operations::divide())
	);
	operators_.insert(
		std::pair<std::string, operations::modulo*>("mod", new operations::modulo())
	);
	operators_.insert(
		std::pair<std::string, operations::negate*>("neg", new operations::negate())
	);
	operators_.insert(
		std::pair<std::string, operations::absolute*>("abs", new operations::absolute())
	);
	operators_.insert(
		std::pair<std::string, operations::increment*>("inc", new operations::increment())
	);
	operators_.insert(
		std::pair<std::string, operations::decrement*>("dec", new operations::decrement())
	);

	// String operations
	operators_.insert(
		std::pair<std::string, operations::duplicate*>("dup", new operations::duplicate())
	);
	operators_.insert(
		std::pair<std::string, operations::reverse*>("rev", new operations::reverse())
	);
	operators_.insert(
		std::pair<std::string, operations::slice*>("slc", new operations::slice())
	);
	operators_.insert(
		std::pair<std::string, operations::index*>("idx", new operations::index())
	);
	operators_.insert(
		std::pair<std::string, operations::concat*>("cat", new operations::concat())
	);
	operators_.insert(
		std::pair<std::string, operations::length*>("len", new operations::length())
	);
	operators_.insert(
		std::pair<std::string, operations::rotate*>("rot", new operations::rotate())
	);
	operators_.insert(
		std::pair<std::string, operations::new_line*>("enl", new operations::new_line())
	);

	 // Test & jumps
	operators_.insert(
		std::pair<std::string, operations::go_to*>("gto", new operations::go_to())
	);
	// operators["geq"] = nullptr;
	operators_.insert(
		std::pair<std::string, operations::goto_not_equal*>("gne", new operations::goto_not_equal())
	);
	operators_.insert(
		std::pair<std::string, operations::goto_less*>("glt", new operations::goto_less())
	);
	operators_.insert(
		std::pair<std::string, operations::goto_less_equal*>("gle", new operations::goto_less_equal())
	);
	operators_.insert(
		std::pair<std::string, operations::goto_greater*>("ggt", new operations::goto_greater())
	);
	operators_.insert(
		std::pair<std::string, operations::goto_greater_equal*>("gge", new operations::goto_greater_equal())
	);

	// Functions
	operators_.insert(
		std::pair<std::string, operations::function*>("fun", new operations::function())
	);
	operators_.insert(
		std::pair<std::string, operations::function_return*>("ret", new operations::function_return())
	);
	operators_.insert(
		std::pair<std::string, operations::end*>("end", new operations::end())
	);


	 // Not a keyword operation. This operation has a value.
	operators_.insert(
		std::pair<std::string, operations::string*>("\\", new operations::string())
	);

	operators_.insert(
		std::pair<std::string, operations::label*>(":", new operations::label())
	);

	operators_.insert(
		std::pair<std::string, operations::label_read*>(">", new operations::label_read())
	);

	operators_.insert(
		std::pair<std::string, operations::variable*>("=", new operations::variable)
	);

	operators_.insert(
		std::pair<std::string, operations::variable_read*>("$", new operations::variable_read)
	);

	operators_.insert(
		std::pair<std::string, operations::integer*>("*", new operations::integer())
	);

}

operations::base* operation_factory::get_operation(std::string& line)
{
	const auto first_char = line[0];
	auto* op = operators_[std::string(1, first_char)];

	if (is_number(line)) op = operators_["*"];
	if (op == nullptr) op = operators_[line];

	// Still null no operation!
	if (op == nullptr)
	{
		std::cout << "No operation found for line: " << line << std::endl;
		return nullptr;
	}

	return op;
}

operation_factory::~operation_factory() {
	for (auto it = operators_.begin(); it != operators_.end(); ++it)
		delete it->second;
}










