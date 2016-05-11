#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include "Czolg.h"
#include <SFML/Audio.hpp>
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



	sf::Texture menu_bg;

	sf::Texture menu_bg_bullets;

	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music music;
	



private:
	
};

#endif