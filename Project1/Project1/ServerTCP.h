#pragma once

#ifndef _SERVERTCP_H
#define _SERVERTCP_H
#include <SFML/Network.hpp>
#include <iostream>
class ServerTCP
{
public:
	ServerTCP();
	~ServerTCP();

	void server_creation();

	void client_connection();

private:
	

};


#endif