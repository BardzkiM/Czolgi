#pragma once

#ifndef _CLIENTTCP_H
#define _CLIENTTCP_H
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
class ClientTCP
{
public:
	ClientTCP();
	~ClientTCP();

	virtual void Run();	

private:
	

};


#endif