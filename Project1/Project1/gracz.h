#pragma once
#include <string>
#include "Czolg.h"
#ifndef gracz_h
#define gracz_h
class gracz
{
public:
	gracz();
	~gracz();
	int id_gracza;
	//string player_name;
	char team;
	int id_server;
	//Czolg tank;
	int score;
};

#endif