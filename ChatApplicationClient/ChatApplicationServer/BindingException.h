#pragma once
#include <exception>

class BindingException
{
public:
	BindingException() {}

	~BindingException(void);

	virtual const char* what() const throw()
	{
		return "Creating The Binding Failed!";
		system("PAUSE");
	}
};

