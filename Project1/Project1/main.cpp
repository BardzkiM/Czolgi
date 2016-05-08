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


using namespace std;
sf::RenderWindow window(sf::VideoMode(1200, 900), "CZOLGI");
Mapa mapa;
Czolg tank;




bool sprawdzKolizjePociskPrzeszkoda(char direction)
{
	int mapa_przeszkody_size = mapa.przeszkody.size();
	int tank_pociski_size = tank.pociski.size();
	switch (direction)
	{
	case 'u':
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{
			for (int j = 0; j <tank_pociski_size; j++)
			{
				if (((tank.pociski[j].x + tank.pociski[j].width) > mapa.przeszkody[i].x) &&
					(tank.pociski[j].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank.pociski[j].y + tank.pociski[j].height) > mapa.przeszkody[i].y) &&
					(tank.pociski[j].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height + tank.pociski[j].movement)))
				{
					//tank.pociski.erase(j);
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
				if (((tank.pociski[j].x + tank.pociski[j].width) > mapa.przeszkody[i].x) &&
					(tank.pociski[j].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank.pociski[j].y + tank.pociski[j].height + tank.pociski[j].movement) > mapa.przeszkody[i].y) && //jak zmienimy pocisk.height na pocisk.width to si� zmienia bug tekstury...
					(tank.pociski[j].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
				{
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
				if (((tank.pociski[j].x + tank.pociski[j].height) > mapa.przeszkody[i].x) &&
					(tank.pociski[j].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width + tank.pociski[j].movement)) &&
					((tank.pociski[j].y + tank.pociski[j].height) > mapa.przeszkody[i].y) &&
					(tank.pociski[j].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
				{
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
				if (((tank.pociski[j].x + tank.pociski[j].width + tank.pociski[j].movement) > mapa.przeszkody[i].x) &&
					(tank.pociski[j].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank.pociski[j].y + tank.pociski[j].height) > mapa.przeszkody[i].y) &&
					(tank.pociski[j].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
				{
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
			if (tank.y - tank.movement < 0)
			{
				return true;
				break;
			}
			for (int i = 0; i <mapa_przeszkody_size; i++)
			{

				if (((tank.x + mapa.przeszkody[i].width) > mapa.przeszkody[i].x) &&
					(tank.x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank.y + mapa.przeszkody[i].height) > mapa.przeszkody[i].y) &&
					(tank.y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height + tank.movement)))
					return true;
			}
			break;
		case 'd':
			if ((tank.y + tank.height + tank.movement) > 900)
				return true;
			for (int i = 0; i <mapa_przeszkody_size; i++)
			{

				if (((tank.x + mapa.przeszkody[i].width) > mapa.przeszkody[i].x) &&
					(tank.x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank.y + mapa.przeszkody[i].height + tank.movement) > mapa.przeszkody[i].y) &&
					(tank.y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
					return true;
			}
			break;
		case 'l':
			if (tank.x - tank.movement < 0)
				return true;
			for (int i = 0; i <mapa_przeszkody_size; i++)
			{

				if (((tank.x + mapa.przeszkody[i].width) > mapa.przeszkody[i].x) &&
					(tank.x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width + tank.movement)) &&
					((tank.y + mapa.przeszkody[i].height) > mapa.przeszkody[i].y) &&
					(tank.y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
					return true;
			}
			break;
		case'r':
			if ((tank.x + tank.width + tank.movement) > 1200)
				return true;
			for (int i = 0; i <mapa_przeszkody_size; i++)
			{

				if (((tank.x + mapa.przeszkody[i].width + tank.movement) > mapa.przeszkody[i].x) &&
					(tank.x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank.y + mapa.przeszkody[i].height) > mapa.przeszkody[i].y) &&
					(tank.y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
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
sf::Thread server_thread(&ServerTCP::Run, &servertcp);	//ustawienie w�tku jako funkcji w Klasie ServerTCP
sf::Thread clienttcp_thread(&ClientTCP::Run, &clienttcp);
sf::Thread clienttcp_thread1(&ClientTCP::Run, &clienttcp1);
sf::Sprite spriteMap(mapa.texture);
sf::CircleShape shape(100.f); //ko�o
sf::Sprite tank_sprite;

sf::Sprite pociska;
sf::Sprite przeszkodaSprite;
void gra()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		tank_sprite.setTexture(tank.textureu);
		tank.angle = 90;
		if (!sprawdzKolizjeCzolgPrzeszkoda('u'))
		{
			
			tank.moveUp();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		tank_sprite.setTexture(tank.textured);
		tank.angle = 270;
		if (!sprawdzKolizjeCzolgPrzeszkoda('d'))
		{
			
			tank.moveDown();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		tank_sprite.setTexture(tank.texturer);
		tank.angle = 180;
		if (!sprawdzKolizjeCzolgPrzeszkoda('r'))
		{
			
			tank.moveRight();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		tank_sprite.setTexture(tank.texturel);
		tank.angle = 0;
		if (!sprawdzKolizjeCzolgPrzeszkoda('l'))
		{
			
			tank.moveLeft();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		int nr = 0;
		tank.pociski.clear();
		tank.addPocisk();

		pociska.setTexture(tank.pociski[nr].texture);
		pociska.setPosition(tank.pociski[nr].x, tank.pociski[nr].y);
	}
	if (!tank.pociski.empty())
	{
		//cout << mapa.przeszkody[0].width << " " << mapa.przeszkody[0].height << endl;
		if (tank.pociski[0].angle == 0)
		{
			if (!sprawdzKolizjePociskPrzeszkoda('l'))
			{
				tank.pociski[0].x -= tank.pociski[0].movement;
			}
		}
		if (tank.pociski[0].angle == 90)
		{
			if (!sprawdzKolizjePociskPrzeszkoda('u'))
			{
				tank.pociski[0].y -= tank.pociski[0].movement;
			}
		}
		if (tank.pociski[0].angle == 180)
		{
			if (!sprawdzKolizjePociskPrzeszkoda('r'))
			{
				tank.pociski[0].x += tank.pociski[0].movement;
			}
		}
		if (tank.pociski[0].angle == 270)
		{
			if (!sprawdzKolizjePociskPrzeszkoda('d'))
			{
				tank.pociski[0].y += tank.pociski[0].movement;
			}
		}
		pociska.setPosition(tank.pociski[0].x, tank.pociski[0].y);

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

	if (!tank.pociski.empty())
		window.draw(pociska);
	window.display();
	tank_sprite.setPosition(tank.x, tank.y);
}
int main()
{
	
	klient.uruchomKlienta();
									//stworzenie obiektu klasy
	servertcp.argument = 5;									//przekazanie do klasy argumentu
	
	server_thread.launch();									//uruchomienie w�tku


	ClientTCP clienttcp;											//stworzenie pierwszego klienta
	sf::Thread clienttcp_thread(&ClientTCP::Run, &clienttcp);		//stworzenie w�tku pierwszego klienta
	clienttcp_thread.launch();										//odpalenie pierwszego klienta


	
	clienttcp_thread1.launch();



	//int menu_pos = 1;
	Menu menu;
	bool menu_open = true;
	
	


	///////WINDOW/////////////////


	//sf::Vector2u size(1200, 900);
	//window.setSize(menu.menu_bg.getSize());//set window size - mo�na w konstruktorze podaj��(w,h)

	
	//shape.setPosition(100, 100);
	//shape.setFillColor(sf::Color::Yellow);

	///////PRZYCISK TRZYMANIE BLOKADA////////////
	//window.setKeyRepeatEnabled(false); //przycisk si� wci�nie tylko raz, nawet jak trzymamy



	////////czas//////////////
	/*
	sf::Time time = sf::seconds(5);
	cout << time.asSeconds() << endl;
	*/
	////////clock////////////////
	//sf::Clock clock;

	string msg = "1234567890111213141516171819";
	string dsp = "";
	int index = 0;

	


	/////obraz///////////
	/*sf::Texture texture;
	if (!texture.loadFromFile("tank.png"))
	{
	cout << "nie mo�na za�adowa� pliku" << endl;
	return EXIT_FAILURE;
	}
	sf::Sprite sprite(texture);

	sf::Vector2u movement(10, 10);
	*/
	
	tank.setInitialPosition(0, 0);
	tank_sprite.setPosition(tank.x, tank.y);

	
	//Przeszkoda Przeszkoda();

	menu.set_bg(&window);
	menu.set_menu_pos_1(&window);

	sf::Clock clock;

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
					/*if (menu_pos == 1)
					{
					menu_pos = 3;
					}
					else {
					menu_pos--;
					}
					menu.set_auto_menu_pos(menu_pos, &window);
					/*tank_sprite.setTexture(tank.textureu);
					tank.moveUp();*/
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					menu.key_down(&window);
					/*if (menu_pos == 3)
					{
					menu_pos = 1;
					}
					else
					{
					menu_pos++;
					}
					menu.set_auto_menu_pos(menu_pos, &window);
					/*tank_sprite.setTexture(tank.textured);
					tank.moveDown();*/
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))//ODPALENIE GRY
				{
					if (menu.position == 1)
					{
						menu_open = false;
						tank_sprite.setTexture(tank.texturel);
					}
					if (menu.position == 3)
					{
						window.close();
						break;
					}

				}
			}
			
			//tank_sprite.setTexture(tank.texture);
			






			//if (event.type == sf::Event::KeyPressed)
			//{
			//	if (event.key.code == sf::Keyboard::Right /*&& event.key.control*/) //KEY drugi mo�e by� tylko po event.key.* np alt control itp
			//	{
			//		system("cls");
			//		cout << index;
			//		index++;
			//	}
			//}
			
		}
		if (!menu_open)
		{
			if(clock.getElapsedTime().asMilliseconds() > 30)
			{
				clock.restart();
				gra();
			}
			

		}
		
		/////////////////zdarzenie////////////////////////
		/* blokuje i czeka na jakikolwiek event
		if (window.waitEvent(event))
		{
		cout << "enet" << endl;
		}
		*/

		/////time////////////
		/*time = clock.getElapsedTime();
		cout << time.asSeconds() << endl;
		clock.restart();
		*/
		//window.draw(tank_spriteImage);
		//window.clear();
		//window.draw(shape);
		//window.display();
	}
	return EXIT_SUCCESS;

	//return 0;
}

