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
	int position;

	int set_bg(sf::RenderWindow * window);

	int set_menu_pos_1(sf::RenderWindow * window);

	int set_menu_pos_2(sf::RenderWindow * window);

	int set_menu_pos_3(sf::RenderWindow * window);

	int set_auto_menu_pos(sf::RenderWindow * window);

	void key_up(sf::RenderWindow * window);

	void key_down(sf::RenderWindow * window);

	void key_enter(sf::RenderWindow *window);







private:
	sf::Texture menu_bg;
};

#endif