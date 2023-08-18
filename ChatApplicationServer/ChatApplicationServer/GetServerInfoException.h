#pragma once
#include <exception>

class GetServerInfoException
{
public:
	GetServerInfoException() {}

	~GetServerInfoException(void);

	virtual const char* what() const throw()
	{
		return "Get Server Info Failed!";
	}
};

