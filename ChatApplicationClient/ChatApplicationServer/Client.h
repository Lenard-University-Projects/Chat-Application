#pragma once

#include "Comms.h"

//Exceptions
#include "ConnectException.h"

class Client : public Comms
{
public:
	ConnectException EConnect;

public:
	Client();
	virtual void PrintMessage() { cout << "This is the client class" << endl; }

	void ConnectToServer()throw(ConnectException);
};