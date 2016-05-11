#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include "Czolg.h"
#include "Menu.h"
#include "Klient.h"
#include "Mapa.h"
#include "ServerTCP.h"
#include "ClientTCP.h"
#include <vector>
#include "Wykonawcy.h"

using namespace std;
sf::RenderWindow window(sf::VideoMode(1200, 900), "CZOLGI");
Mapa mapa;
Czolg tank[4];





bool sprawdzKolizjePociskPrzeszkoda(char direction)
{
	int mapa_przeszkody_size = mapa.przeszkody.size();
	int tank_pociski_size = tank[0].pociski.size();
	switch (direction)
	{
	case 'u':
		if (tank[0].y - tank[0].movement < 0)
		{
			return true;
			break;
		}
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{
			for (int j = 0; j <tank_pociski_size; j++)
			{
				if (((tank[0].pociski[j].x + tank[0].pociski[j].width) > mapa.przeszkody[i].x) &&
					(tank[0].pociski[j].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank[0].pociski[j].y + tank[0].pociski[j].height) > mapa.przeszkody[i].y) &&
					(tank[0].pociski[j].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height + tank[0].pociski[j].movement)))
				{
					//tank.pociski[j].
					//if (!tank.pociski.empty())
					//daæ do tank remove pocisk
					tank[0].removePocisk(j);
					return true;
				}
			}
		}
		break;
	case 'd':
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{
			for (int j = 0; j <tank_pociski_size; j++)
			{
				if (((tank[0].pociski[j].x + tank[0].pociski[j].width) > mapa.przeszkody[i].x) &&
					(tank[0].pociski[j].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank[0].pociski[j].y + tank[0].pociski[j].height + tank[0].pociski[j].movement) > mapa.przeszkody[i].y) && //jak zmienimy pocisk.height na pocisk.width to siê zmienia bug tekstury...
					(tank[0].pociski[j].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
				{
					tank[0].removePocisk(j);
					return true;
				}
			}
		}
		break;
	case 'l':
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{
			for (int j = 0; j <tank_pociski_size; j++)
			{
				if (((tank[0].pociski[j].x + tank[0].pociski[j].height) > mapa.przeszkody[i].x) &&
					(tank[0].pociski[j].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width + tank[0].pociski[j].movement)) &&
					((tank[0].pociski[j].y + tank[0].pociski[j].height) > mapa.przeszkody[i].y) &&
					(tank[0].pociski[j].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
				{
					tank[0].removePocisk(j);
					return true;
				}
			}
		}
		break;
	case'r':
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{
			for (int j = 0; j <tank_pociski_size; j++)
			{
				if (((tank[0].pociski[j].x + tank[0].pociski[j].width + tank[0].pociski[j].movement) > mapa.przeszkody[i].x) &&
					(tank[0].pociski[j].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank[0].pociski[j].y + tank[0].pociski[j].height) > mapa.przeszkody[i].y) &&
					(tank[0].pociski[j].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
				{
					tank[0].removePocisk(j);
					return true;
				}
			}
		}
		break;
	default: 
		break;
	}
	return false;
}
//////// komyntosz
bool sprawdzKolizjeCzolgPrzeszkoda(char direction)
{
	int mapa_przeszkody_size = mapa.przeszkody.size();	
		switch (direction)
		{
		case 'u':
			if (tank[0].y - tank[0].movement < 0)
			{
				return true;
				break;
			}
			for (int i = 0; i <mapa_przeszkody_size; i++)
			{

				if (((tank[0].x + mapa.przeszkody[i].width) > mapa.przeszkody[i].x) &&
					(tank[0].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank[0].y + mapa.przeszkody[i].height) > mapa.przeszkody[i].y) &&
					(tank[0].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height + tank[0].movement)))
					return true;
			}
			break;
		case 'd':
			if ((tank[0].y + tank[0].height + tank[0].movement) > 900)
				return true;
			for (int i = 0; i <mapa_przeszkody_size; i++)
			{

				if (((tank[0].x + mapa.przeszkody[i].width) > mapa.przeszkody[i].x) &&
					(tank[0].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank[0].y + mapa.przeszkody[i].height + tank[0].movement) > mapa.przeszkody[i].y) &&
					(tank[0].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
					return true;
			}
			break;
		case 'l':
			if (tank[0].x - tank[0].movement < 0)
				return true;
			for (int i = 0; i <mapa_przeszkody_size; i++)
			{

				if (((tank[0].x + mapa.przeszkody[i].width) > mapa.przeszkody[i].x) &&
					(tank[0].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width + tank[0].movement)) &&
					((tank[0].y + mapa.przeszkody[i].height) > mapa.przeszkody[i].y) &&
					(tank[0].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
					return true;
			}
			break;
		case'r':
			if ((tank[0].x + tank[0].width + tank[0].movement) > 1200)
				return true;
			for (int i = 0; i <mapa_przeszkody_size; i++)
			{

				if (((tank[0].x + mapa.przeszkody[i].width + tank[0].movement) > mapa.przeszkody[i].x) &&
					(tank[0].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank[0].y + mapa.przeszkody[i].height) > mapa.przeszkody[i].y) &&
					(tank[0].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
					return true;
			}
			break;

		default:
			break;

	}
		return false;
}
Client klient("127.0.0.1");
ServerTCP servertcp;
ClientTCP clienttcp;
ClientTCP clienttcp1;
sf::Thread server_thread(&ServerTCP::Run, &servertcp);	//ustawienie w¹tku jako funkcji w Klasie ServerTCP
sf::Thread clienttcp_thread(&ClientTCP::Run, &clienttcp);
sf::Thread clienttcp_thread1(&ClientTCP::Run, &clienttcp1);
sf::Sprite spriteMap(mapa.texture);
sf::CircleShape shape(100.f); //ko³o
sf::Sprite tank_sprite;

sf::Sprite pociska;
sf::Sprite przeszkodaSprite;
sf::Clock bullet_clock;
void gra()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		tank_sprite.setTexture(tank[0].textureu);
		tank[0].angle = 90;
		if (!sprawdzKolizjeCzolgPrzeszkoda('u'))
		{
			
			tank[0].moveUp();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		tank_sprite.setTexture(tank[0].textured);
		tank[0].angle = 270;
		if (!sprawdzKolizjeCzolgPrzeszkoda('d'))
		{
			
			tank[0].moveDown();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		tank_sprite.setTexture(tank[0].texturer);
		tank[0].angle = 180;
		if (!sprawdzKolizjeCzolgPrzeszkoda('r'))
		{
			
			tank[0].moveRight();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		tank_sprite.setTexture(tank[0].texturel);
		tank[0].angle = 0;
		if (!sprawdzKolizjeCzolgPrzeszkoda('l'))
		{
			
			tank[0].moveLeft();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		int nr = 0;
		//tank.pociski.clear();
		cout << "Zegar dla pocisku: " << bullet_clock.getElapsedTime().asMilliseconds()  << endl;
		if(bullet_clock.getElapsedTime().asMilliseconds()>1000)
		{ 
			tank[0].addPocisk();
			bullet_clock.restart();
		}
			
		
		//pociska.setTexture(tank.pociski[nr].texture);
		//pociska.setPosition(tank.pociski[nr].x, tank.pociski[nr].y);
	}
	if (!tank[0].pociski.empty())
	{
		//cout << mapa.przeszkody[0].width << " " << mapa.przeszkody[0].height << endl;
		if (tank[0].pociski[0].angle == 0)
		{
			if (!sprawdzKolizjePociskPrzeszkoda('l'))
			{
				tank[0].pociski[0].x -= tank[0].pociski[0].movement;
			}
		}
		else if (tank[0].pociski[0].angle == 90)
		{
			if (!sprawdzKolizjePociskPrzeszkoda('u'))
			{
				tank[0].pociski[0].y -= tank[0].pociski[0].movement;
			}
		}
		else if (tank[0].pociski[0].angle == 180)
		{
			if (!sprawdzKolizjePociskPrzeszkoda('r'))
			{
				tank[0].pociski[0].x += tank[0].pociski[0].movement;
			}
		}
		else if (tank[0].pociski[0].angle == 270)
		{
			if (!sprawdzKolizjePociskPrzeszkoda('d'))
			{
				tank[0].pociski[0].y += tank[0].pociski[0].movement;
			}
		}
		if(!tank[0].pociski.empty())
			pociska.setPosition(tank[0].pociski[0].x, tank[0].pociski[0].y);

	}
	//cout << "jestem" << endl;
	window.clear();
	// Draw the tank_sprite
	window.draw(spriteMap);
	window.draw(tank_sprite);

	for (int i = 0; i < mapa.przeszkody.size(); i++)
	{
		przeszkodaSprite.setTexture(mapa.przeszkody[i].texture);
		przeszkodaSprite.setPosition(mapa.przeszkody[i].x, mapa.przeszkody[i].y);
		window.draw(przeszkodaSprite);
	}

	if (!tank[0].pociski.empty())
	{
		for (int i = 0; i < tank[0].pociski.size(); i++)
		{
			pociska.setTexture(tank[0].pociski[i].texture);
			pociska.setPosition(tank[0].pociski[i].x, tank[0].pociski[i].y);
			window.draw(pociska);
		}
	}
	window.display();
	tank_sprite.setPosition(tank[0].x, tank[0].y);
}
int main()
{
	
										
	//servertcp.argument = 5;										//przekazanie do klasy argumentu	
	server_thread.launch();											//uruchomienie w¹tku			
	clienttcp_thread.launch();										//odpalenie pierwszego klienta	
	clienttcp_thread1.launch();										//odpalenie drugiego klienta



	//int menu_pos = 1;
	Wykonawcy wykonawcy;
	Menu menu;
	bool menu_open = true;
	
	

	///////PRZYCISK TRZYMANIE BLOKADA////////////
	//window.setKeyRepeatEnabled(false); //przycisk siê wciœnie tylko raz, nawet jak trzymamy



	string msg = "1234567890111213141516171819";
	string dsp = "";
	int index = 0;

	

	
	tank[0].setInitialPosition(0, 0);
	tank_sprite.setPosition(tank[0].x, tank[0].y);

	
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
						tank_sprite.setTexture(tank[0].texturel);
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
				gra();
			}
			

		}
		

	}
	return EXIT_SUCCESS;

	//return 0;
}
