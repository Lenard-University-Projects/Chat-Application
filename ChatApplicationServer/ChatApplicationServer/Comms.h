#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>

// Exceptions
#include "SendMsgException.h"
#include "WinsockDllException.h"
#include "GetSocketException.h"
#include "CreateThreadException.h"

using namespace std;

////////////////////////////////////////////////////////////////////
/// Struct will be used to pass multiple parameters to the Thread //
/// that will be receive all the incoming messages				  //
////////////////////////////////////////////////////////////////////
struct ThreadRecvMsgStruct {
	SOCKET Socket;
	string CurrSystem;
	int& MessageYPos;
};

class Comms
{
private:
	int MessageYPos;

	SendMsgException		ESendMsg;
	WinsockDllException		EWinsockDLL;
	GetSocketException		EGetSocket;
	CreateThreadException	ECreateThread;

public:
	SOCKADDR_STORAGE from;				// Storing the address of the client
	SOCKET comSocket, acceptSocket;		// Description of the socket used

	char hostStr[NI_MAXHOST]; // Storing incoming client IP
	char portStr[NI_MAXSERV]; // Storing incoming client Port

	int port = 55555;

protected:
	virtual void SetCursorPos(int x, int y);

public:
	virtual void PrintMessage() = 0;

	virtual void LookWinsockDllUp()throw(WinsockDllException);
	virtual void OpenSocket()throw(GetSocketException);

	virtual void ReceiveMessage(string System)throw(CreateThreadException);
	virtual void SendMessages(string System)throw(SendMsgException);
};