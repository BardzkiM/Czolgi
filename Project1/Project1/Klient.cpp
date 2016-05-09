#define WIN32_LEAN_AND_MEAN

#include "Klient.h"
#include "Obiekt.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
// link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "8888" 
#define DEFAULT_BUFFER_LENGTH	512

/////////////////**********************************************************************************
Client::Client(char* servername)
{
	szServerName = servername;
	ConnectSocket = INVALID_SOCKET;
	std::cout << "Klient zostal uruchomiony!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
}
/////////////////**********************************************************************************
//Start the Client
bool Client::Start() {
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return false;
	}

	struct addrinfo	*result = NULL,
		*ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(szServerName, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return false;
	}

	ptr = result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %d\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return false;
	}

	// Connect to server
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

	if (iResult == SOCKET_ERROR)
	{
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		return false;
	}

	return true;
};
/////////////////**********************************************************************************
// Free the resouces
void Client::Stop() {
	int iResult = shutdown(ConnectSocket, SD_SEND);

	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed: %d\n", WSAGetLastError());
	}

	closesocket(ConnectSocket);
	WSACleanup();
};

/////////////////**********************************************************************************
// Send message to server
bool Client::Send(char* szMsg)
{

	int iResult = send(ConnectSocket, szMsg, strlen(szMsg), 0);

	if (iResult == SOCKET_ERROR)
	{
		printf("send failed: %d\n", WSAGetLastError());
		Stop();
		return false;
	}

	return true;
};

/////////////////**********************************************************************************
// Receive message from server
bool Client::Recv()
{
	char recvbuf[DEFAULT_BUFFER_LENGTH];
	int iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFFER_LENGTH, 0);

	if (iResult > 0)
	{
		char msg[DEFAULT_BUFFER_LENGTH];
		memset(&msg, 0, sizeof(msg));
		strncpy_s(msg, recvbuf, iResult); //strncpy_s - "bezpieczniejsze" niz strncpy

		printf("Received: %s\n", msg);

		return true;
	}
	return false;
};

/////////////////**********************************************************************************
int Client::uruchomKlienta()
{
	std::string msg;
	std::vector<std::string> data;
	//do maina:
	//Client client("127.0.0.1");
	Obiekt obiekt; //obiekt, ktorego elementy bedziemy przesylac

	if (!Start())
		return 1;

	while (true)
	{
		std::cout << "Send: ";
		std::getline(std::cin, msg);

		// Close the connection when user enter "close"
		if (msg.compare("close") == 0)
		{
			break;
		}

		std::string msg2 = ""; //string, by mozna go bylo wyslac za pomoca 'Send', ktorego parametrem sa wskazniki
		data = obiekt.zwrocNazwe(); //data- vector, w ktorym sa przechowywane elementy do wyslania
		for (int i = 0; i < data.size(); i++)
		{
			msg2 += data.at(i) + " "; //dodajemy kazdy element z vectora do stringa
		}

		Send((char*)msg2.c_str());
		Recv();
	}

	Stop();

	getchar();
	return 0;
};