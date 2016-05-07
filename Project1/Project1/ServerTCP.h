#pragma once

#ifndef _SERVERTCP_H
#define _SERVERTCP_H
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
class ServerTCP
{
public:
	ServerTCP();
	~ServerTCP();

	void accept_client();

	void receive(int which_client);

	void listen();

	int argument;
	void Run(int argument);

	void Run();
	
private:
	sf::TcpListener listener; // tworzymy gniazdo nas³uchujace
	sf::TcpSocket *client = NULL;// new sf::TcpSocket[1];

	int nr_of_clients=0;

};


#endif