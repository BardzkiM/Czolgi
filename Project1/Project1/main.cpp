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


Czolg tank[4];





//////// komyntosz

ServerTCP servertcp;
ClientTCP clienttcp;
ClientTCP clienttcp1;
sf::Thread server_thread(&ServerTCP::Run, &servertcp);	//ustawienie w�tku jako funkcji w Klasie ServerTCP
sf::Thread clienttcp_thread(&ClientTCP::Run, &clienttcp);
sf::Thread clienttcp_thread1(&ClientTCP::Run, &clienttcp1);

sf::CircleShape shape(100.f); //ko�o
sf::Sprite tank_sprite;

sf::Sprite pociska;
sf::Sprite przeszkodaSprite;
sf::Clock bullet_clock;
sf::RenderWindow window(sf::VideoMode(1200, 900), "CZOLGI");


void gra(Czolg &tank)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		tank_sprite.setTexture(tank.textureu);
		tank.angle = 90;
		if (!(tank.sprawdzKolizjeCzolgPrzeszkoda()))
		{
			
			tank.move(0,-1);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		tank_sprite.setTexture(tank.textured);
		tank.angle = 270;
		if (!(tank.sprawdzKolizjeCzolgPrzeszkoda()))
		{
			
			tank.move(0,1);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		tank_sprite.setTexture(tank.texturer);
		tank.angle = 180;
		if (!(tank.sprawdzKolizjeCzolgPrzeszkoda()))
		{
			
			tank.move(1,0);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		tank_sprite.setTexture(tank.texturel);
		tank.angle = 0;
		if (!(tank.sprawdzKolizjeCzolgPrzeszkoda()))
		{
			
			tank.move(-1, 0);
		}
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

	window.clear();
	// Draw the tank_sprite
	window.draw(GraDane::spriteMapa);
	window.draw(tank_sprite);

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
	tank_sprite.setPosition(tank.x, tank.y);
}
int main()
{
	Czolg tank;
	GraDane::mapa;
	sf::Sprite spritemapa(GraDane::mapa.texture);
	GraDane::spriteMapa = spritemapa;

									//stworzenie obiektu klasy
	servertcp.argument = 5;									//przekazanie do klasy argumentu
	
	//server_thread.launch();									//uruchomienie w�tku

	tank.serialize();
	//std::cout << "Serializacja: " <<temp_string.str().c_str();
	ClientTCP clienttcp;											//stworzenie pierwszego klienta
	sf::Thread clienttcp_thread(&ClientTCP::Run, &clienttcp);		//stworzenie w�tku pierwszego klienta
	//clienttcp_thread.launch();										//odpalenie pierwszego klienta


	
	//clienttcp_thread1.launch();



	//int menu_pos = 1;
	Wykonawcy wykonawcy;
	Menu menu;
	bool menu_open = true;
	
	

	///////PRZYCISK TRZYMANIE BLOKADA////////////
	//window.setKeyRepeatEnabled(false); //przycisk si� wci�nie tylko raz, nawet jak trzymamy



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
