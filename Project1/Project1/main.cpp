#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include "Czolg.h"
#include "Menu.h"
#include "GraDane.h"
#include "ServerTCP.h"
#include "ClientTCP.h"
#include <vector>
#include "Wykonawcy.h"

using namespace std;








//////// komyntosz
Czolg tank;
ServerTCP servertcp;
ClientTCP clienttcp(&tank);
ClientTCP clienttcp1(&tank);
sf::Thread server_init(&ServerTCP::RunInit, &servertcp);	//ustawienie w¹tku jako funkcji w Klasie ServerTCP
sf::Thread server_game(&ServerTCP::runGame, &servertcp);	//ustawienie w¹tku jako funkcji w Klasie ServerTCP
sf::Thread clienttcp_thread(&ClientTCP::RunInit, &clienttcp);
sf::Thread clienttcp_thread1(&ClientTCP::RunInit, &clienttcp1);

sf::CircleShape shape(100.f); //ko³o
sf::Sprite tank_sprite;

sf::Sprite tanks_sprite[4];

sf::Sprite pociska;
sf::Sprite przeszkodaSprite;
sf::Clock bullet_clock;
sf::RenderWindow window(sf::VideoMode(1200, 900), "CZOLGI");


void gra(Czolg &tank)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		tank.angle = 90;
		tank.move(0,-1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		tank.angle = 270;
		tank.move(0,1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		tank.angle = 180;
		tank.move(1,0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		tank.angle = 0;
		tank.move(-1, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		int nr = 0;
		//tank.pociski.clear();
		cout << "Zegar dla pocisku: " << bullet_clock.getElapsedTime().asMilliseconds()  << endl;
		if(bullet_clock.getElapsedTime().asMilliseconds()>1000)
		{ 
			tank.addPocisk();
			bullet_clock.restart();
		}
		
		//pociska.setTexture(tank.pociski[nr].texture);
		//pociska.setPosition(tank.pociski[nr].x, tank.pociski[nr].y);
	}
	tank.sprawdzKolizjePociskowPrzeszkod();

	

	for (int i = 0; i < GraDane::mapa.przeszkody.size(); i++)
	{
		przeszkodaSprite.setTexture(GraDane::mapa.przeszkody[i].texture);
		przeszkodaSprite.setPosition(GraDane::mapa.przeszkody[i].x, GraDane::mapa.przeszkody[i].y);
		window.draw(przeszkodaSprite);
	}

	if (!tank.pociski.empty())
	{
		for (int i = 0; i < tank.pociski.size(); i++)
		{
			pociska.setTexture(tank.pociski[i].texture);
			pociska.setPosition(tank.pociski[i].x, tank.pociski[i].y);
			window.draw(pociska);
		}
	}
	window.display();

	tank_sprite.setTexture(tank.texture);
	tank_sprite.setPosition(tank.x, tank.y);

	for (int i = 0; i < clienttcp.nr_of_clients; i++)
	{
		if (i == tank.nr_czolgu)
			continue;
		clienttcp.tanks[i].setRotation();
		tanks_sprite[i].setPosition(clienttcp.tanks[i].x, clienttcp.tanks[i].y);
		tanks_sprite[i].setTexture(clienttcp.tanks[i].texture);
		window.draw(tanks_sprite[i]);
	}
	window.clear();
	// Draw the tank_sprite
	window.draw(GraDane::spriteMapa);
	window.draw(tank_sprite);
}
int main()
{
	
	GraDane::mapa;
	sf::Sprite spritemapa(GraDane::mapa.texture);
	GraDane::spriteMapa = spritemapa;
	//server_init.launch();
	
	

	ClientTCP clienttcp(&tank);										//stworzenie pierwszego klienta
	sf::Thread clienttcp_thread(&ClientTCP::RunInit, &clienttcp);		//stworzenie w¹tku pierwszego klienta
	clienttcp_thread.launch();										//odpalenie pierwszego klienta	
	//clienttcp_thread1.launch();



	//int menu_pos = 1;
	Wykonawcy wykonawcy;
	Menu menu;
	bool menu_open = true;
	
	

	///////PRZYCISK TRZYMANIE BLOKADA////////////
	//window.setKeyRepeatEnabled(false); //przycisk siê wciœnie tylko raz, nawet jak trzymamy



	string msg = "1234567890111213141516171819";
	string dsp = "";
	int index = 0;

	

	
	tank.setInitialPosition(0, 0);
	tank_sprite.setPosition(tank.x, tank.y);

	
	//Przeszkoda Przeszkoda();

	menu.set_bg(&window);
	menu.set_menu_pos_1(&window);

	sf::Clock clock;
	
	sf::Music music;
	sf::Music musicTank;
	if (!music.openFromFile("sounds/musicBG.ogg"))
	{
		std::cerr << "blad czytania muzyki w tle!" << std::endl;
		exit(-12);
	}
	if (!musicTank.openFromFile("sounds/tankMusic.ogg"))
	{
		std::cerr << "blad czytania muzyki w tle!" << std::endl;
		exit(-12);
	}

	music.play();
	music.setLoop(true);
	musicTank.setLoop(true);

	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// Close window: exit
			case sf::Event::Closed:
				window.close();
				break;
			}
			if (menu_open == true)
			{
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					
					menu.key_up(&window);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					
					menu.key_down(&window);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))//ODPALENIE GRY
				{
					if (menu.position == 1)
					{
						menu_open = false;
						tank_sprite.setTexture(tank.texturel);
						music.stop();
						musicTank.play();
						server_init.terminate();
						server_game.launch();

						
					}
					if (menu.position == 2) //wykonawcy
					{
						menu_open = false;
						wykonawcy.set_bg(&window);
						
					}
					if (menu.position == 3)
					{
						window.close();
						break;
					}

				}
			}
			
			//tank_sprite.setTexture(tank.texture);
			

			
		}
		
		if (!menu_open&&menu.position == 1)
		{
			if(clock.getElapsedTime().asMilliseconds() > 30)
			{
				clock.restart();
				gra(tank);
			}
			

		}
		

	}
	return EXIT_SUCCESS;
	
	//return 0;
}
