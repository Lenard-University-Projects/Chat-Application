#include "stdafx.h"
#include "Comms.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>
#include <assert.h>

//Exceptions
#include "WinsockDllException.h"

using namespace std;

///////////////////////////////////////////////////////////////////////
/// All the incoming messages will be placed inside a thread so they //
/// can run	simultaneously with the send method						 //	 
///////////////////////////////////////////////////////////////////////
DWORD WINAPI ReceiveMessageThread(LPVOID structParam)
{
	ThreadRecvMsgStruct* threadStruct = (ThreadRecvMsgStruct*)structParam;
	SOCKET socket = threadStruct->Socket;

	int bytesRecv = SOCKET_ERROR;
	char recvBuffer[200] = "";

	while (true)
	{
		if (socket != INVALID_SOCKET)
		{
			bytesRecv = recv(socket, recvBuffer, 200, 0);

			if (bytesRecv < 0)
			{
				cout << "\n" << "Connection Closed!" << endl;
				system("PAUSE");
			}
			else
			{
				if (strlen(recvBuffer) > 0)
				{
					// Creating a new COORD variable
					COORD pos = { 0, threadStruct->MessageYPos };

					// Position the received message in the new position
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
					cout << threadStruct->CurrSystem << ": " << recvBuffer << endl;

					// Increment the position first before using it
					threadStruct->MessageYPos++;
				}
			}

			if (strcmp(recvBuffer, "QUIT") == 0 && threadStruct->CurrSystem == "Client")
			{
				shutdown(socket, SD_SEND);
				socket = INVALID_SOCKET;
				break;
			}
		}
	}

	closesocket(socket);
	exit(0);
	return 0;
}

///////////////////////////////////////////////////////////////////////
/// In order to position some of the text displayed in the console   //
/// use this method													 //
///////////////////////////////////////////////////////////////////////
void Comms::SetCursorPos(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

///////////////////////////////////////////////////////////////////////
/// Loading the WinSock DLL											 //
///////////////////////////////////////////////////////////////////////
void Comms::LookWinsockDllUp()throw(WinsockDllException)
{
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);

	int wsaErr;
	wsaErr = WSAStartup(wVersionRequested, &wsaData);

	if (wsaErr != 0)
		throw(EWinsockDLL);
}

///////////////////////////////////////////////////////////////////////
/// Opening the socket for both the client and server				 //
///////////////////////////////////////////////////////////////////////
void Comms::OpenSocket()throw(GetSocketException)
{
	comSocket = INVALID_SOCKET;
	comSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (comSocket == INVALID_SOCKET)
	{
		WSACleanup();
		throw(EGetSocket);
	}
	else
		MessageYPos = 3;
}

///////////////////////////////////////////////////////////////////////
/// Checking if we are the server or client and creating the 		 //
/// appropriate thread that will be responsible for handleing the    //
/// received messages and displaying them							 //
///////////////////////////////////////////////////////////////////////
void Comms::ReceiveMessage(string System)throw(CreateThreadException)
{
	if (System == "Server")
	{
		//Creating a new struct and assigning values to the properties
		ThreadRecvMsgStruct* threadStruct = new ThreadRecvMsgStruct{ acceptSocket, "Client", MessageYPos };

		DWORD recvThreadID;
		HANDLE recvThread = CreateThread(NULL, 0, ReceiveMessageThread, (LPVOID)threadStruct, 0, &recvThreadID);

		// After storing the created thread check if is valid or not and run the code block.
		if (!recvThread)
		{
			closesocket(acceptSocket);
			closesocket(comSocket);
			WSACleanup();
			throw(ECreateThread);
		}
	}
	else if (System == "Client")
	{
		//Creating a new struct and assigning values to the properties
		ThreadRecvMsgStruct* threadStruct = new ThreadRecvMsgStruct{ comSocket, "Server", MessageYPos };

		DWORD recvThreadID;
		HANDLE recvThread = CreateThread(NULL, 0, ReceiveMessageThread, (LPVOID*)threadStruct, 0, &recvThreadID);

		// After storing the created thread check if is valid or not and run the code block.
		if (!recvThread)
		{
			closesocket(acceptSocket);
			closesocket(comSocket);
			WSACleanup();
			throw(ECreateThread);
		}
	}
}

///////////////////////////////////////////////////////////////////////
/// Checking if we are the server or client and creating the 		 //
/// appropriate thread												 //
///////////////////////////////////////////////////////////////////////
void Comms::SendMessages(string System)throw(SendMsgException)
{
	int byteCount = SOCKET_ERROR;
	char sendBuffer[500] = "";

	if (System == "Server")
	{
		while (true)
		{
			SetCursorPos(5, 1);
			cout << "Enter your message: ";

			SetCursorPos(25, 1);
			cin.getline(sendBuffer, 1024);

			if (strlen(sendBuffer) > 0 && strlen(sendBuffer) < 200)
			{
				// Storing the total number of bytes sent
				byteCount = send(acceptSocket, sendBuffer, 200, 0);

				// Throwing an exceptions if there is an error with byteCount
				if (byteCount == SOCKET_ERROR)
					throw(ESendMsg);
				else
				{
					SetCursorPos(0, MessageYPos);
					cout << "Server: " << sendBuffer << endl;

					// Move the cursor at the beginning of the line which will prepare the next stage
					// which is to add spaces so we remove the previous entered message
					SetCursorPos(0, 1);
					cout << "\r";

					for (int i = 0; i < (25 + strlen(sendBuffer)); i++)
					{
						SetCursorPos(i, 1);
						cout << " ";
					}

					// Reset the buffer and increment the message position
					sendBuffer[0] = 0;
					MessageYPos++;
				}

				// Exiting the application if QUIT is typed into the console CLIENT-ONLY
				if (strcmp(sendBuffer, "QUIT") == 0)
					exit(0);
			}
			else
			{
				sendBuffer[0] = 0;
				cout << "Message is either empty or too long max 200 characters!" << endl;
			}
		}
	}
	else if (System == "Client")
	{
		while (true)
		{
			SetCursorPos(5, 1);
			cout << "Enter your message: ";

			SetCursorPos(25, 1);
			cin.getline(sendBuffer, 1024);

			if (strlen(sendBuffer) > 0 && strlen(sendBuffer) < 150)
			{
				// Storing the total number of bytes sent
				byteCount = send(comSocket, sendBuffer, 500, 0);

				// Throwing an exceptions if there is an error with byteCount
				if (byteCount == SOCKET_ERROR)
					throw(ESendMsg);
				else
				{
					SetCursorPos(0, MessageYPos);
					cout << "Client: " << sendBuffer << endl;
					
					// Move the cursor at the beginning of the line which will prepare the next stage
					// which is to add spaces so we remove the previous entered message
					SetCursorPos(0, 1);
					cout << "\r";

					for (int i = 0; i < (25 + strlen(sendBuffer)); i++)
					{
						SetCursorPos(i, 1);
						cout << " ";
					}

					// Reset the buffer and increment the message position
					sendBuffer[0] = 0;
					MessageYPos++;
				}

				// Exiting the application if QUIT is typed into the console CLIENT-ONLY
				if (strcmp(sendBuffer, "QUIT") == 0)
					exit(0);
			}
			else
			{
				sendBuffer[0] = 0;
				cout << "Message is either empty or too long max 200 characters!" << endl;
			}
		}
	}
}