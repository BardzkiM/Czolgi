#pragma once
#include "Czolg.h"
#ifndef _GRACZ_H
#define _GRACZ_H
class Gracz
{
public:
	Gracz();
	~Gracz();
	int id_gracza;
	std::string player_name;
	char team;
	int id_server;
	Czolg tank;
	int score;
};

#endif


