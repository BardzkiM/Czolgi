#pragma once

#ifndef _CLIENTTCP_H
#define _CLIENTTCP_H
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Czolg.h"
#include "GraDane.h"

class ClientTCP
{
public:
	
	ClientTCP(Czolg * source_tank_pointer);
	~ClientTCP();
	
	static int nr_of_clients;
	void deserialize(std::string stream);

	void send(std::string message);

	std::string receive();

	void RunInit();
	std::string numer_klienta;
	
	static Czolg tanks[3];
	std::string adress;

private:
	sf::TcpSocket socket;
	Czolg *tank;

	

};


#endif