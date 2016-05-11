#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <math.h>


#ifndef _WYKONAWCY_H
#define _WYKONAWCY_H

class Wykonawcy
{
public:
	Wykonawcy();
	~Wykonawcy();
	
	sf::Texture wykonawcy_bg;
	sf::Text wstep;
	sf::Text wykonawca1;
	sf::Text wykonawca2;
	sf::Text wykonawca3;
	sf::Text wykonawca4;
	sf::Text wykonawca5;

	sf::SoundBuffer buffer;
	sf::Sound sound;

	int set_bg(sf::RenderWindow * window);
	sf::Text napisy(sf::Text text, std::string nazwa, float x, float y, bool style, int size);

	
private:

};

#endif