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
sf::Thread server_init(&ServerTCP::RunInit, &servertcp);	//ustawienie w¹tku jako funkcji w Klasie ServerTCP
sf::Thread server_game(&ServerTCP::runGame, &servertcp);	//ustawienie w¹tku jako funkcji w Klasie ServerTCP
ClientTCP clienttcp(&tank, &mutex);										//stworzenie pierwszego klienta
sf::Thread clienttcp_thread(&ClientTCP::RunInit, &clienttcp);		//stworzenie w¹tku pierwszego klienta


sf::Sprite przeszkodaSprite;
sf::Clock bullet_clock;
sf::RenderWindow window(sf::VideoMode(1200, 900), "CZOLGI");

Czolg *czolg;

bool gameready = false;

int ClientTCP::nr_of_clients = 0;
Czolg ClientTCP::tanks[3];

Menu menu;

void rysujPociski(int i)
{
	Pocisk * pocisk;
	for (int j = 0; j < czolg->pociski.size(); j++)
	{
		pocisk = &ClientTCP::tanks[i].pociski[j];
		pocisk->setRotation();
		window.draw(pocisk->sprite);
	}
}
void rysujMape()
{
	window.draw(GraDane::spriteMapa);
	for (int i = 0; i < GraDane::mapa.przeszkody.size(); i++)
	{
		przeszkodaSprite.setTexture(GraDane::mapa.przeszkody[i].texture);
		przeszkodaSprite.setPosition(GraDane::mapa.przeszkody[i].x, GraDane::mapa.przeszkody[i].y);
		window.draw(przeszkodaSprite);
	}
}

void obslugaKlawiatury()
{
	//obs³uga klawiatury
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		tank.angle = 90;
		tank.move(0, -1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		tank.angle = 270;
		tank.move(0, 1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		tank.angle = 180;
		tank.move(1, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		tank.angle = 0;
		tank.move(-1, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		int nr = 0;
		if (bullet_clock.getElapsedTime().asMilliseconds()>1000)
		{
			tank.strzelilem = true;
			bullet_clock.restart();
		}

	}
}

void gra()
{
	
	obslugaKlawiatury();
	window.clear();

	tank.setRotation();
	tank.setBar();

	rysujMape();
	window.draw(tank.hpBar);
	window.draw(tank.sprite);
	
	mutex.lock();
	for (int i = 0; i < ClientTCP::nr_of_clients; i++)
	{
		czolg = &ClientTCP::tanks[i];
		if (i != tank.nr_czolgu)
		{
			czolg->setRotation();
			czolg->setBar();

			//ustalenie pozycji HP BAR
			window.draw(czolg->sprite);
			window.draw(czolg->hpBar);
		}
		rysujPociski(i);
	}
	mutex.unlock();

	window.display();
	
}
void drawMenu()
{
	menu.set_bg(&window);
	menu.set_menu_pos_1(&window);
}
void gameOver()
{
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (!buffer.loadFromFile("sounds/gameover.wav"))
	{
		std::cerr << "blad czytania dzwieku! (gameover.wav)" << std::endl;
		exit(-12);
	}
	sound.setBuffer(buffer);
	sound.play();
	
	std::cout << "Game Over" << std::endl;
	clienttcp_thread.terminate();
	server_game.terminate();
	tank.x = -100;
	tank.y = -100;
	sf::Texture logoOver;
	logoOver.loadFromFile("images/game_over.png");
	sf::Sprite logoOverSprite;
	logoOverSprite.setTexture(logoOver);
	sf::Sprite gameOver;
	sf::Texture texture2;
	texture2.loadFromImage(window.capture());
	
	gameOver.setTexture(texture2);
	gameOver.scale(1.5, 1.5);
	for (int i = 0; i < 316; i++)
	{
		window.clear();
		window.draw(gameOver);
		logoOverSprite.setPosition(420, i);
		window.draw(logoOverSprite);
		window.display();
	}
	sf::sleep(sf::milliseconds(500));
}
int main()
{
	sf::Vector2u vect(800, 600);
	window.setSize(vect);
	window.setPosition(sf::Vector2i(550, 0));
	GraDane::mapa;
	sf::Sprite spritemapa(GraDane::mapa.texture);
	GraDane::spriteMapa = spritemapa;
	//server_init.launch();
	
	




	//int menu_pos = 1;
	Wykonawcy wykonawcy;
	LoadingPage loadingpage(&server_init, &server_game, &clienttcp_thread, &clienttcp);
	
	bool menu_open = true;
	

	
	tank.setInitialPosition(0, 0);

	
	//Przeszkoda Przeszkoda();

	drawMenu();

	sf::Clock clock;
	
	sf::Music music;
	sf::Music musicTank;
	if (!music.openFromFile("sounds/musicBG.ogg"))
	{
		std::cerr << "blad czytania muzyki w tle!(musicBG.ogg)" << std::endl;
		exit(-12);
	}
	if (!musicTank.openFromFile("sounds/tankMusic.ogg"))
	{
		std::cerr << "blad czytania muzyki w tle! (tankMusic.ogg)" << std::endl;
		exit(-12);
	}

	music.play();
	music.setLoop(true);
	musicTank.setLoop(true);
	sf::Event event;
	while (window.isOpen())
	{
		// Process events
		
		
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
						//clienttcp_thread.launch();
						music.stop();
						musicTank.play();
						gameready = true;
				
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
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				if(menu.position==2)
				{
					menu_open = true;
					//menu.position = 1;
					
					drawMenu();
					menu.set_menu_pos_2(&window);
				}
				else
				{
					window.close();
					break;
				}
			}
			

			
		}
		
		if (!menu_open && gameready==true)
		{
			if(clock.getElapsedTime().asMilliseconds() > 30)
			{
				clock.restart();
				if (tank.hp > 0)
				{
					gra();
					
				}
				else
				{
					gameOver();
					gameready = false;
				}
			}
			

		}
		

	}
	return EXIT_SUCCESS;
	
	//return 0;
}
