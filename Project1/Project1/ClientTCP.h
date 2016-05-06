#pragma once

#ifndef _CLIENTTCP_H
#define _CLIENTTCP_H
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
class ClientTCP: public sf::Thread
{
public:
	
	~ClientTCP();

	

	

private:
	virtual void Run();

};


#endif