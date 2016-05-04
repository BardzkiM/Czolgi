#pragma once
#include "gracz.h"
#include <SFML/Graphics.hpp>
#include "Przeszkoda.h"
#include <iostream>
#ifndef _MAPA_H
#define _MAPA_H
class Mapa
{
public:
	Mapa();
	~Mapa();
	std::vector <gracz> gracze;
	std::vector <Przeszkoda> przeszkody;
	int przeszkodyTablica[20][15];
	
	void initializeMap();
	void setPlayers();
	sf::Texture texture;

};

#endif

