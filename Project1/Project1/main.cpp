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
#include "LoadingPage.h"


using namespace std;




sf::Mutex mutex;



//////// komyntosz
Czolg tank;
ServerTCP servertcp;
//ClientTCP clienttcp(&tank, &mutex);
//ClientTCP clienttcp1(&tank);
sf::Thread server_init(&ServerTCP::RunInit, &servertcp);	//ustawienie w¹tku jako funkcji w Klasie ServerTCP
sf::Thread server_game(&ServerTCP::runGame, &servertcp);	//ustawienie w¹tku jako funkcji w Klasie ServerTCP
//sf::Thread clienttcp_thread(&ClientTCP::RunInit, &clienttcp);
//sf::Thread clienttcp_thread1(&ClientTCP::RunInit, &clienttcp1);

sf::CircleShape shape(100.f); //ko³o
sf::Sprite tank_sprite;
sf::Sprite tanks_sprite[4];
sf::Sprite tank_enemy_sprite[3];
sf::Sprite enemyBar[4];
sf::Sprite myBar;

sf::Sprite pociska[100];
sf::Sprite przeszkodaSprite;
sf::Clock bullet_clock;
sf::RenderWindow window(sf::VideoMode(1200, 900), "CZOLGI");

bool gameready = false;

int ClientTCP::nr_of_clients = 0;
Czolg ClientTCP::tanks[3];

void ustaleniePozycjiBar(Czolg *czolg, int index)
{
	if (czolg->y < 17)
		enemyBar[index].setPosition(czolg->x, czolg->y + czolg->height + 3);
	else
		enemyBar[index].setPosition(czolg->x, czolg->y - 17);
	czolg->setBar();
}
void ustaleniePozycjiBar()
{
	if (tank.y < 17)
		myBar.setPosition(tank.x, tank.y + tank.height + 3);
	else
		myBar.setPosition(tank.x, tank.y - 17);
	tank.setBar();
}
void rysujPociski(Czolg *czolg, int i)
{
	Pocisk * pocisk;
	for (int j = 0; j < czolg->pociski.size(); j++)
	{
		pocisk = &ClientTCP::tanks[i].pociski[j];
		pocisk->setRotation();
		pociska[j].setPosition(pocisk->x, pocisk->y);
		pociska[j].setTexture(pocisk->texture);
		window.draw(pociska[j]);
	}
}
void rysujPociski()
{
	for (int j = 0; j < tank.pociski.size(); j++)
	{
		tank.pociski[j].setRotation();
		pociska[j].setPosition(tank.pociski[j].x, tank.pociski[j].y);
		pociska[j].setTexture(tank.pociski[j].texture);
		window.draw(pociska[j]);
	}
}
 
void gra(Czolg &tank)
{
	//obs³uga klawiatury
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
		//cout << "Zegar dla pocisku: " << bullet_clock.getElapsedTime().asMilliseconds()  << endl;
		if(bullet_clock.getElapsedTime().asMilliseconds()>1000)
		{ 
			tank.strzelilem = true;
			bullet_clock.restart();
		}
		
	}

	window.clear();
	// Draw the tank_sprite
	window.draw(GraDane::spriteMapa);
	//window.draw(tank_sprite);


	//rysowanie mapy
	for (int i = 0; i < GraDane::mapa.przeszkody.size(); i++)
	{
		przeszkodaSprite.setTexture(GraDane::mapa.przeszkody[i].texture);
		przeszkodaSprite.setPosition(GraDane::mapa.przeszkody[i].x, GraDane::mapa.przeszkody[i].y);
		window.draw(przeszkodaSprite);
	}

	

	tank_sprite.setTexture(tank.texture);
	tank_sprite.setPosition(tank.x, tank.y);

	ustaleniePozycjiBar();
	myBar.setTexture(tank.textureBar);
	window.draw(myBar);

	

	
	Czolg *czolg;
	
	window.draw(tank_sprite);




	//rysowanie czo³gów klientów i ich pocisków
	std::cout << "Przed mutexem main" << std::endl;
	mutex.lock();
	std::cout << "Po mutex main" << std::endl;
	for (int i = 0; i < ClientTCP::nr_of_clients; i++)
	{
		czolg = &ClientTCP::tanks[i];
		if (i != tank.nr_czolgu)
		{
			czolg->setRotation();
			tanks_sprite[i].setPosition(czolg->x, czolg->y);
			tanks_sprite[i].setTexture(czolg->texture);
			window.draw(tanks_sprite[i]);

			//ustalenie pozycji HP BAR
			ustaleniePozycjiBar(czolg, i);

			enemyBar[i].setTexture(czolg->textureBar);
			window.draw(enemyBar[i]);
		}
			rysujPociski(czolg, i);
		
		
	}
	std::cout << "Po mutex main 2" << std::endl;
	mutex.unlock();
	std::cout << "Po mutex main 3" << std::endl;

	window.display();
	//window.clear();
	// Draw the tank_sprite
	
}
void gameOver()
{
	tank.x = -100;
	tank.y = -100;
}
int main()
{
	sf::Vector2u vect(800, 600);
	window.setSize(vect);
	window.setPosition(sf::Vector2i(100, 0));
	GraDane::mapa;
	sf::Sprite spritemapa(GraDane::mapa.texture);
	GraDane::spriteMapa = spritemapa;
	//server_init.launch();
	
	

	ClientTCP clienttcp(&tank, &mutex);										//stworzenie pierwszego klienta
	sf::Thread clienttcp_thread(&ClientTCP::RunInit, &clienttcp);		//stworzenie w¹tku pierwszego klienta
	//clienttcp_thread.launch();										//odpalenie pierwszego klienta	
	//clienttcp_thread1.launch();



	//int menu_pos = 1;
	Wykonawcy wykonawcy;
	LoadingPage loadingpage(&server_init, &server_game);
	Menu menu;
	bool menu_open = true;
	

	
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
						clienttcp.adress=loadingpage.run(&window);
						clienttcp_thread.launch();
						tank_sprite.setTexture(tank.texturel);
						music.stop();
						musicTank.play();
						//server_init.terminate();
						//server_game.launch();
						gameready = true;

						/*menu_open = false;
						tank_sprite.setTexture(tank.texturel);
						music.stop();
						musicTank.play();
						server_init.terminate();
						server_game.launch();
*/
						
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
		
		if (!menu_open && gameready==true)
		{
			if(clock.getElapsedTime().asMilliseconds() > 30)
			{
				clock.restart();
				if (tank.hp > 0)
				{
					gra(tank);
				}
				else
				{
					gameOver();
				}
			}
			

		}
		

	}
	return EXIT_SUCCESS;
	
	//return 0;
}
