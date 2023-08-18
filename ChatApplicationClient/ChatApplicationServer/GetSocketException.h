#pragma once
#include <exception>

class GetSocketException
{
public:
	GetSocketException() {}

	~GetSocketException(void);

	virtual const char* what() const throw()
	{
		return "Opening The Socket Failed!";
		system("PAUSE");
	}
};

