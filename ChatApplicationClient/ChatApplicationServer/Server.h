#pragma once

#include "Comms.h"

//Exceptions
#include "BindingException.h"
#include "ListenToConnException.h"
#include "AcceptConnectionException.h"
#include "GetServerInfoException.h"

class Server : public Comms
{
private:
	BindingException			EBinding;
	ListenToConnException		EListenConnecections;
	AcceptConnectionException	EAcceptConnection;
	GetServerInfoException		EGetServerInfo;

public:
	Server();
	virtual void PrintMessage() { cout << "This is the server class" << endl; }

	void CreateBinding();
	void ListenToConnections();
	void AcceptConnection();
};