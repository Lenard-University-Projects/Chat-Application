#pragma once
#include <exception>

class ListenToConnException
{
public:
	ListenToConnException() {}

	~ListenToConnException(void);

	virtual const char* what() const throw()
	{
		return "Listening For Connections Failed!";
	}
};

