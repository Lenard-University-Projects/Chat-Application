#pragma once
#include <exception>

class AcceptConnectionException
{
public:
	AcceptConnectionException() {}

	~AcceptConnectionException(void);

	virtual const char* what() const throw()
	{
		return "Accepting Connection Failed!";
		system("PAUSE");
	}
};

