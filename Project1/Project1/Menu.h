#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include "Czolg.h"

#ifndef _MENU_H
#define _MENU_H

class Menu
{
public:
	Menu();
	~Menu();

	int set_bg(sf::RenderWindow * window);
	


private:
	sf::Texture menu_bg;
};

#endif