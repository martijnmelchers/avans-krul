#pragma once
#include <map>
#include <string>

#include "IOperation.h"


class operation_factory
{
private:
	std::map<std::string, operations::base*> operators_;

public:
	operation_factory();
	~operation_factory();
	
	operations::base* get_operation(std::string& line);
};
