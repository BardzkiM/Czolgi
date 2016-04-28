#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include "Czolg.h"


using namespace std;

int main()
{
	sf::Sprite pociska;
	///////WINDOW/////////////////
	sf::RenderWindow window(sf::VideoMode(800, 600), "KOLO");

	//sf::Vector2u size(800, 600);
	//window.setSize(size);//set window size - mo¿na w konstruktorze podaj¹æ(w,h)

	sf::CircleShape shape(100.f); //ko³o
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

	Czolg tank;
	
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
	sf::Sprite sprite(tank.texturel);
	tank.x =100;
	tank.y =100;
	sprite.setPosition(tank.x, tank.y);


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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (tank.angle == 0)
				{
					tank.x -= 5;
				}
				if (tank.angle == 90)
				{
					tank.y -= 5;
				}
				if (tank.angle == 180)
				{
					tank.x += 5;
				}
				if (tank.angle == 270)
				{
					tank.y += 5;
				}
				sprite.setPosition(tank.x, tank.y);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (tank.angle == 0)
				{
					tank.x += 5;
				}
				if (tank.angle == 90)
				{
					tank.y += 5;
				}
				if (tank.angle == 180)
				{
					tank.x -= 5;
				}
				if (tank.angle == 270)
				{
					tank.y -= 5;
				}
				sprite.setPosition(tank.x, tank.y);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				//sprite.move(30,0);
				tank.angle += 90;
				if (tank.angle == 360)
					tank.angle = 0;
				if (tank.angle == -90)
					tank.angle = 270;
				
				if (tank.angle == 0)
				{
					sprite.setTexture(tank.texturel);
				}
				if (tank.angle == 90)
				{
					sprite.setTexture(tank.textureu);
				}
				if (tank.angle == 180)
				{
					sprite.setTexture(tank.texturer);
				}
				if (tank.angle == 270)
				{
					sprite.setTexture(tank.textured);
				}


				
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				//sprite.move(-30, 0);
				tank.angle -= 90;
				if (tank.angle == 360)
					tank.angle = 0;
				if (tank.angle == -90)
					tank.angle = 270;

				if (tank.angle == 0)
				{
					sprite.setTexture(tank.texturel);
				}
				if (tank.angle == 90)
				{
					sprite.setTexture(tank.textureu);
				}
				if (tank.angle == 180)
				{
					sprite.setTexture(tank.texturer);
				}
				if (tank.angle == 270)
				{
					sprite.setTexture(tank.textured);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				int nr = 0;
				tank.pociski.clear();
				tank.addPocisk();
				pociska.setTexture(tank.pociski[nr].texture);
				tank.pociski[nr].angle = tank.angle;
				
				if (tank.angle == 0)
				{
					tank.pociski[nr].x = tank.x;
					tank.pociski[nr].y = tank.y + (tank.height / 2);

					pociska.setPosition(tank.pociski[nr].x, tank.pociski[nr].y);
				}
				if (tank.angle == 90)
				{
					tank.pociski[nr].x = tank.x + (tank.width / 2);
					tank.pociski[nr].y = tank.y;
					
					pociska.setPosition(tank.pociski[nr].x, tank.pociski[nr].y);
				}
				if (tank.angle == 180)
				{
					tank.pociski[nr].x = tank.x + tank.width;
					tank.pociski[nr].y = tank.y + (tank.height / 2);
					
					pociska.setPosition(tank.pociski[nr].x, tank.pociski[nr].y);
				}
				if (tank.angle == 270)
				{
					tank.pociski[nr].x = tank.x + tank.width / 2;
					tank.pociski[nr].y = tank.y + tank.height;
					
					pociska.setPosition(tank.pociski[nr].x, tank.pociski[nr].y);
				}

				pociska.rotate(tank.pociski[nr].angle);

				//cout << "pocisk "/* << tank.pociski[nr].x << " " << tank.pociski[nr].y */<<" " << tank.pociski[nr].angle << endl;
				cout << "tank " << tank.x << " " << tank.y << " " << tank.angle << endl;
				cout << "sprite " << sprite.getPosition().x << "  " << sprite.getPosition().y << " " << sprite.getRotation() << endl;
				cout << endl;
				//window.draw(pociska);
			}








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
		// Clear screen
		window.clear();
		// Draw the sprite
		window.draw(sprite);
		//if (!tank.pociski.empty())
			window.draw(pociska);

		window.display();











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
		//window.draw(spriteImage);
		//window.clear();
		//window.draw(shape);
		//window.display();
	}
	return EXIT_SUCCESS;

	//return 0;
}