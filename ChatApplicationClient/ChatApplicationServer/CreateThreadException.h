#pragma once
#include <exception>

class CreateThreadException
{
public:
	CreateThreadException() {}

	~CreateThreadException(void);

	virtual const char* what() const throw()
	{
		return "Error CreatingThread!";
		system("PAUSE");
	}
};

