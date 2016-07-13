
#pragma once

#include "EngineLayer.h"

class A_StarException : public std::exception
{
private:
	std::string message;
public:
	A_StarException(std::string);
	~A_StarException() throw();

	const char * what() const throw();
};