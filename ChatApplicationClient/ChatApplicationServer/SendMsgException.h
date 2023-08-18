#pragma once
#include <exception>

class SendMsgException
{
public:
	SendMsgException() {}

	~SendMsgException(void);

	virtual const char* what() const throw()
	{
		return "Sending Message Failed!";
		system("PAUSE");
	}
};

