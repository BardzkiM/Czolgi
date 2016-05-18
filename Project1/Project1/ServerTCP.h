#pragma once

#ifndef _SERVERTCP_H
#define _SERVERTCP_H
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Czolg.h"

class ServerTCP
{

public:
	ServerTCP();
	~ServerTCP();

	std::string serialize();

	void accept_client();
	void send(int which_client, std::string message);
	void receive(int which_client);
	int argument = 0;
	int ilosc_graczy = 0;
	
	void RunInit();
	void runGame();
	void sprawdzKolizjePociskCzolg(int index);
	void sprawdzKolizjePociskCzolgs();
	Czolg tank[4];
	
private:

	sf::TcpListener listener; // tworzymy gniazdo nas³uchujace
	//sf::TcpSocket *client = NULL;// new sf::TcpSocket[1];
	int nr_of_clients=0;
	sf::TcpSocket client[4];
	

};


#endif