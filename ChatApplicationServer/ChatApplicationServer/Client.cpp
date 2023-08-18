#include "stdafx.h"
#include "Client.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>

using namespace std;

Client::Client() { }

////////////////////////////////////////////////////////////////////
/// Once the client is ready and everything checked out he can	  //
/// then connect to a server using a local IP (127.0.0.1)
////////////////////////////////////////////////////////////////////
void Client::ConnectToServer()throw(ConnectException)
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;

	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.S_un);
	clientService.sin_port = htons(port);

	// We will try to conenct using the informations provited and if it fails
	// clean up the socket and throw and exception
	if (connect(comSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		WSACleanup();
		throw(EConnect);
	}
	else
	{
		SetCursorPos(5, 0); // Position the text 5 units to the right
		cout << "Client: Connected" << endl;
	}
}
