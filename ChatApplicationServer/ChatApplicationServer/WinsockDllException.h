#pragma once
#include <exception>

class WinsockDllException
{
public:
	WinsockDllException() {}

	~WinsockDllException(void);

	virtual const char* what() const throw() 
	{
		return "The Winsock DLL not found!";
	}
};

