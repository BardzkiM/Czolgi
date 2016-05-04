#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include "Czolg.h"
#include "Menu.h"
#include "Klient.h"
#include "Mapa.h"

using namespace std;
sf::RenderWindow window(sf::VideoMode(1200, 900), "CZOLGI");
Mapa mapa;
Czolg tank;

bool sprawdzKolizjeCzolgPrzeszkoda(char direction)
{
	switch (direction)
	{
	case 'u':
		for (int i = 0; i < mapa.przeszkody.size(); i++)
		{

			if (((tank.x + 60) > mapa.przeszkody[i].x) &&
				(tank.x < (mapa.przeszkody[i].x + 60)) &&
				((tank.y + 60) > mapa.przeszkody[i].y) &&
				(tank.y < (mapa.przeszkody[i].y + 65)))
				return true;
		}
		return false;
		break;
	case 'd':
		for (int i = 0; i < mapa.przeszkody.size(); i++)
		{

			if (((tank.x + 60) > mapa.przeszkody[i].x) &&
				(tank.x < (mapa.przeszkody[i].x + 60)) &&
				((tank.y + 65) > mapa.przeszkody[i].y) &&
				(tank.y < (mapa.przeszkody[i].y + 60)))
				return true;
		}
		return false;
		break;
	case 'l':
		for (int i = 0; i < mapa.przeszkody.size(); i++)
		{

			if (((tank.x + 60) > mapa.przeszkody[i].x) &&
				(tank.x < (mapa.przeszkody[i].x + 65)) &&
				((tank.y + 60) > mapa.przeszkody[i].y) &&
				(tank.y < (mapa.przeszkody[i].y + 60)))
				return true;
		}
		return false;
		break;
	case'r':
		for (int i = 0; i < mapa.przeszkody.size(); i++)
		{

			if (((tank.x + 65) > mapa.przeszkody[i].x) &&
				(tank.x < (mapa.przeszkody[i].x + 60)) &&
				((tank.y + 60) > mapa.przeszkody[i].y) &&
				(tank.y < (mapa.przeszkody[i].y + 60)))
				return true;
		}
		return false;
		break;
	}
	
}
int main()
{
	Client klient("127.0.0.1");
	klient.uruchomKlienta();
	//int menu_pos = 1;
	Menu menu;
	bool menu_open = true;
	
	sf::Sprite spriteMap(mapa.texture);


	///////WINDOW/////////////////


	//sf::Vector2u size(1200, 900);
	//window.setSize(menu.menu_bg.getSize());//set window size - mo¿na w konstruktorze podaj¹æ(w,h)

	sf::CircleShape shape(100.f); //ko³o
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
	sf::Sprite tank_sprite;
	
	sf::Sprite pociska;
	tank.setInitialPosition(0, 0);
	tank_sprite.setPosition(tank.x, tank.y);

	sf::Sprite przeszkodaSprite;
	//Przeszkoda Przeszkoda();

	menu.set_bg(&window);
	menu.set_menu_pos_1(&window);


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
					menu_open = false;
					//window.setSize(size);
					tank_sprite.setTexture(tank.texturel);
				}
			}
			else if (!menu_open)
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

					//pociska.rotate(tank.pociski[nr].angle);

					//cout << "pocisk " << tank.pociski[nr].x << " " << tank.pociski[nr].y <<" " << tank.pociski[nr].angle << "----------" << tank.pociski[nr].height << " " << tank.pociski[nr].width <<  endl;
					//cout << "tank " << tank.x << " " << tank.y << " " << tank.angle << endl;
					//cout << "tank_sprite " << tank_sprite.getPosition().x << "  " << tank_sprite.getPosition().y << " " << tank_sprite.getRotation() << endl;
					//cout << endl;
					//window.draw(pociska);
				}
			}
			//tank_sprite.setTexture(tank.texture);
			tank_sprite.setPosition(tank.x, tank.y);






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
		if (!tank.pociski.empty())
		{
			//cout << "jestem!!!!!!!!!!" << endl;
			if (tank.pociski[0].angle == 0)
			{
				tank.pociski[0].x -= 1;
			}
			if (tank.pociski[0].angle == 90)
			{
				tank.pociski[0].y -= 1;
			}
			if (tank.pociski[0].angle == 180)
			{
				tank.pociski[0].x += 1;
			}
			if (tank.pociski[0].angle == 270)
			{
				tank.pociski[0].y += 1;
			}
			pociska.setPosition(tank.pociski[0].x, tank.pociski[0].y);

		}


		///GAME GAME GAME
		// Clear screen
		if (!(menu_open))
		{
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