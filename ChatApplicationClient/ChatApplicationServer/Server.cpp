#include "stdafx.h"
#include "Server.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>

using namespace std;

Server::Server() { }

///////////////////////////////////////////////////////////////////////
/// Creating the binding and cleaning everything as well as throwing //
/// an exception is it returns an ERROR								 //
///////////////////////////////////////////////////////////////////////
void Server::CreateBinding()throw(BindingException)
{
	sockaddr_in service;
	service.sin_family = AF_INET;

	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.S_un);
	service.sin_port = htons(port);

	if (bind(comSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		closesocket(comSocket);
		WSACleanup();

		throw(EBinding);
	}
}

///////////////////////////////////////////////////////////////////////
/// Listening to any connections, also throw an exception if there	 //
/// was an issue with the socket									 //
///////////////////////////////////////////////////////////////////////
void Server::ListenToConnections()throw(ListenToConnException)
{
	if (listen(comSocket, 1) == SOCKET_ERROR)
		throw(EListenConnecections);
	else
	{
		SetCursorPos(5, 0); // Position the text 5 units to the right
		cout << "Waiting for connections..." << endl;
	}
}

///////////////////////////////////////////////////////////////////////
/// Once the connection is open and we can have clients connecting	 //
/// get some information from them and accept the connection.		 //
///////////////////////////////////////////////////////////////////////
void Server::AcceptConnection()throw(AcceptConnectionException,GetServerInfoException)
{
	int retval, fromlen, socket_type;

	fromlen = sizeof(socket_type);
	retval = getsockopt(comSocket, SOL_SOCKET, SO_TYPE, (char*)&socket_type, &fromlen);
	fromlen = sizeof(from);

	// Storing the clients description into the acceptSocket.
	acceptSocket = accept(comSocket, (SOCKADDR*)&from, &fromlen);

	// Checking for validation, if is not valied clean up the socket and throw an exception
	if (acceptSocket == INVALID_SOCKET)
	{
		WSACleanup();
		throw(EAcceptConnection);
	}

	// Storing the result of the method, if not 0 it means it failed otherwise it is a success
	retval = getnameinfo((SOCKADDR*)&from, fromlen, hostStr, NI_MAXHOST, portStr, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

	// If the value is not 0 (Failed) clean up the socket and throw an exception
	if (retval != 0)
	{
		WSACleanup();
		throw(EGetServerInfo);
	}
}