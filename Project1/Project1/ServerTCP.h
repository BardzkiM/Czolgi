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

	int argument;
	void Run(int argument);

	void Run();
	
private:
	

};


#endif