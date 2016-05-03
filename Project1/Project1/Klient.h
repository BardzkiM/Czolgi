#pragma once
#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
// link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "8888" 
#define DEFAULT_BUFFER_LENGTH	512

#ifndef _KLIENT_H
#define _KLIENT_H
class Client {
public:
	Client(char* servername);
	int uruchomKlienta();
	bool Start();
	void Stop();
	bool Recv();
	bool Send(char* szMsg);

private:
	char* szServerName;
	SOCKET ConnectSocket;
};
#endif