#include "gracz.h"
#include "ServerTCP.h"
#include "Czolg.h"

using namespace std;

//int id_gracza;
//std::string player_name;
//char team;
//int id_server;
//Czolg tank;
//int score;

gracz::gracz(string nickname, char team)
{
	this->player_name = nickname;
	this->team = team;
}


gracz::~gracz()
{
}

