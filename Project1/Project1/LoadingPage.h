#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include "ClientTCP.h"

#ifndef _LOADINGPAGE_H
#define _LOADINGPAGE_H
class LoadingPage
{
public:
	
	LoadingPage(sf::Thread * server_init, sf::Thread * server_game, sf::Thread * client_tcp_thread, ClientTCP * client_tcp);
	~LoadingPage();
	sf::Text napisy(sf::Text text, std::string nazwa, float x, float y, bool style, int size);
	std::string run(sf::RenderWindow * window);

private:

	
	sf::Texture first_background;
	sf::Texture second_background;
	sf::Text text;
	sf::Font font;
	sf::Thread *server_init;
	sf::Thread *server_game;
	sf::Thread *client_tcp_thread;
	ClientTCP *client_tcp;
};

#endif