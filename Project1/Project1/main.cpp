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
					(tank.pociski[j].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height + 1)))
					return true;
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
					((tank.pociski[j].y + tank.pociski[j].height + 1) > mapa.przeszkody[i].y) && //jak zmienimy pocisk.height na pocisk.width to siê zmienia bug tekstury...
					(tank.pociski[j].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
					return true;
			}
		}
		break;
	case 'l':
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{
			for (int j = 0; j <tank_pociski_size; j++)
			{
				if (((tank.pociski[j].x + tank.pociski[j].height) > mapa.przeszkody[i].x) &&
					(tank.pociski[j].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width + 1)) &&
					((tank.pociski[j].y + tank.pociski[j].height) > mapa.przeszkody[i].y) &&
					(tank.pociski[j].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
					return true;
			}
		}
		break;
	case'r':
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{
			for (int j = 0; j <tank_pociski_size; j++)
			{
				if (((tank.pociski[j].x + tank.pociski[j].width + 1) > mapa.przeszkody[i].x) &&
					(tank.pociski[j].x < (mapa.przeszkody[i].x + mapa.przeszkody[i].width)) &&
					((tank.pociski[j].y + tank.pociski[j].height) > mapa.przeszkody[i].y) &&
					(tank.pociski[j].y < (mapa.przeszkody[i].y + mapa.przeszkody[i].height)))
					return true;
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
			if (tank.y - 5 < 0)
			{
				return true;
				break;
			}
			for (int i = 0; i <mapa_przeszkody_size; i++)
			{

				if (((tank.x + 60) > mapa.przeszkody[i].x) &&
					(tank.x < (mapa.przeszkody[i].x + 60)) &&
					((tank.y + 60) > mapa.przeszkody[i].y) &&
					(tank.y < (mapa.przeszkody[i].y + 65)))
					return true;
			}
			break;
		case 'd':
			if ((tank.y + tank.height + 5) > 900)
				return true;
			for (int i = 0; i <mapa_przeszkody_size; i++)
			{

				if (((tank.x + 60) > mapa.przeszkody[i].x) &&
					(tank.x < (mapa.przeszkody[i].x + 60)) &&
					((tank.y + 65) > mapa.przeszkody[i].y) &&
					(tank.y < (mapa.przeszkody[i].y + 60)))
					return true;
			}
			break;
		case 'l':
			if (tank.x - 5 < 0)
				return true;
			for (int i = 0; i <mapa_przeszkody_size; i++)
			{

				if (((tank.x + 60) > mapa.przeszkody[i].x) &&
					(tank.x < (mapa.przeszkody[i].x + 65)) &&
					((tank.y + 60) > mapa.przeszkody[i].y) &&
					(tank.y < (mapa.przeszkody[i].y + 60)))
					return true;
			}
			break;
		case'r':
			if ((tank.x + tank.width + 5) > 1200)
				return true;
			for (int i = 0; i <mapa_przeszkody_size; i++)
			{

				if (((tank.x + 65) > mapa.przeszkody[i].x) &&
					(tank.x < (mapa.przeszkody[i].x + 60)) &&
					((tank.y + 60) > mapa.przeszkody[i].y) &&
					(tank.y < (mapa.przeszkody[i].y + 60)))
					return true;
			}
			break;

		default:
			break;

	}
		return false;
}
//Client klient("127.0.0.1");
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
void gra()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!sprawdzKolizjeCzolgPrzeszkoda('u'))
		{
			tank_sprite.setTexture(tank.textureu);
			tank.moveUp();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (!sprawdzKolizjeCzolgPrzeszkoda('d'))
		{
			tank_sprite.setTexture(tank.textured);
			tank.moveDown();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (!sprawdzKolizjeCzolgPrzeszkoda('r'))
		{
			tank_sprite.setTexture(tank.texturer);
			tank.moveRight();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (!sprawdzKolizjeCzolgPrzeszkoda('l'))
		{
			tank_sprite.setTexture(tank.texturel);
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
				tank.pociski[0].x -= 1;
			}
		}
		if (tank.pociski[0].angle == 90)
		{
			if (!sprawdzKolizjePociskPrzeszkoda('u'))
			{
				tank.pociski[0].y -= 1;
			}
		}
		if (tank.pociski[0].angle == 180)
		{
			if (!sprawdzKolizjePociskPrzeszkoda('r'))
			{
				tank.pociski[0].x += 1;
			}
		}
		if (tank.pociski[0].angle == 270)
		{
			if (!sprawdzKolizjePociskPrzeszkoda('d'))
			{
				tank.pociski[0].y += 1;
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
	
	//klient.uruchomKlienta();
									//stworzenie obiektu klasy
	servertcp.argument = 5;									//przekazanie do klasy argumentu
	
	server_thread.launch();									//uruchomienie w¹tku


	ClientTCP clienttcp;											//stworzenie pierwszego klienta
	sf::Thread clienttcp_thread(&ClientTCP::Run, &clienttcp);		//stworzenie w¹tku pierwszego klienta
	clienttcp_thread.launch();										//odpalenie pierwszego klienta


	
	clienttcp_thread1.launch();



	//int menu_pos = 1;
	Menu menu;
	bool menu_open = true;
	
	Wykonawcy wykonawcy;
	//window.draw(wykonawcy.set_bg);


	///////WINDOW/////////////////


	//sf::Vector2u size(1200, 900);
	//window.setSize(menu.menu_bg.getSize());//set window size - mo¿na w konstruktorze podaj¹æ(w,h)

	
	shape.setPosition(100, 100);
	shape.setFillColor(sf::Color::Yellow);

	///////PRZYCISK TRZYMANIE BLOKADA////////////
	//window.setKeyRepeatEnabled(false); //przycisk siê wciœnie tylko raz, nawet jak trzymamy



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
	cout << "nie mo¿na za³adowaæ pliku" << endl;
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
			






			//if (event.type == sf::Event::KeyPressed)
			//{
			//	if (event.key.code == sf::Keyboard::Right /*&& event.key.control*/) //KEY drugi mo¿e byæ tylko po event.key.* np alt control itp
			//	{
			//		system("cls");
			//		cout << index;
			//		index++;
			//	}
			//}
			
		}
		if (!menu_open&&menu.position==1)
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

