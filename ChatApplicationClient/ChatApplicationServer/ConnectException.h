#pragma once
#include <exception>

class ConnectException
{
public:
	ConnectException() {}

	~ConnectException(void);

	virtual const char* what() const throw()
	{
		return "Failed To Connect To Server!";
		system("PAUSE");
	}
};

