/////////////////////////////////////////////////////////////////////////////////
//
//	Name: Lenard Denisz Pop
//  ScriptName: ChatApplicationClient
//	Notes:
//
//              © DeniszPop. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Comms.h"
#include "Client.h"
#include "Server.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>

#define CURR_SYSTEM "Server"

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main()
{
	try
	{
		if (CURR_SYSTEM == "Client")
		{
			Client* client = new Client();
			client->LookWinsockDllUp();
			client->OpenSocket();
			client->ConnectToServer();

			client->ReceiveMessage(CURR_SYSTEM);
			client->SendMessages(CURR_SYSTEM);
		}
		else if (CURR_SYSTEM == "Server")
		{
			Server* server = new Server();
			server->LookWinsockDllUp();
			server->OpenSocket();
			server->CreateBinding();
			server->ListenToConnections();
			server->AcceptConnection();

			server->ReceiveMessage(CURR_SYSTEM);
			server->SendMessages(CURR_SYSTEM);
		}

		WSACleanup();
	}
	catch (WinsockDllException& e)
	{
		cout << e.what() << endl;
	}
	catch (GetSocketException& e)
	{
		cout << e.what() << endl;
	}
	catch (BindingException& e)
	{
		cout << e.what() << endl;
	}
	catch (ListenToConnException& e)
	{
		cout << e.what() << endl;
	}
	catch (AcceptConnectionException& e)
	{
		cout << e.what() << endl;
	}
	catch (ConnectException& e)
	{
		cout << e.what() << endl;
	}
	catch (CreateThreadException& e)
	{
		cout << e.what() << endl;
	}
	catch (SendMsgException& e)
	{
		cout << e.what() << endl;
	}

	system("pause");
	return 0;
}

