#pragma once
#include "Gracz.h"
#include "Przeszkoda.h"
#ifndef _MAPA_H
#define _MAPA_H
class Mapa
{
public:
	Mapa();
	~Mapa();
	std::vector <Gracz> gracze;
	std::vector <Przeszkoda> przeszkody;
	void initializeMap();
	void setPlayers();


};

#endif

