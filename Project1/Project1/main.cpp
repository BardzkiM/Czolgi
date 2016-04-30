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
	tank.setInitialPosition(100,100);
	sprite.setPosition(tank.x- tank.width/2, tank.y - tank.height / 2);


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
				tank.move(1);
				
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				tank.move(-1);
				
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				tank.rotate(90);
				
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				tank.rotate(-90);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				int nr = 0;
				tank.pociski.clear();
				tank.addPocisk();
				
				
				if (tank.angle == 0)
				{
					tank.pociski[nr].x = tank.x;
					tank.pociski[nr].y = tank.y + (tank.height / 2);
					pociska.setTexture(tank.pociski[nr].texturel);
					pociska.setPosition(tank.pociski[nr].x-tank.pociski[nr].width, tank.pociski[nr].y- (tank.pociski[nr].height/2));
				}
				if (tank.angle == 90)
				{
					tank.pociski[nr].x = tank.x + (tank.width / 2);
					tank.pociski[nr].y = tank.y;
					pociska.setTexture(tank.pociski[nr].textureu);
					pociska.setPosition(tank.pociski[nr].x-(tank.pociski[nr].width/2), tank.pociski[nr].y- tank.pociski[nr].height);
				}
				if (tank.angle == 180)
				{
					tank.pociski[nr].x = tank.x + tank.width;
					tank.pociski[nr].y = tank.y + (tank.height / 2);
					pociska.setTexture(tank.pociski[nr].texturer);
					pociska.setPosition(tank.pociski[nr].x, tank.pociski[nr].y - (tank.pociski[nr].height/2));
				}
				if (tank.angle == 270)
				{
					tank.pociski[nr].x = tank.x + tank.width / 2;
					tank.pociski[nr].y = tank.y + tank.height;
					pociska.setTexture(tank.pociski[nr].textured);
					pociska.setPosition(tank.pociski[nr].x-(tank.pociski[nr].height/2), tank.pociski[nr].y);
				}

				//pociska.rotate(tank.pociski[nr].angle);

				cout << "pocisk " << tank.pociski[nr].x << " " << tank.pociski[nr].y <<" " << tank.pociski[nr].angle << "----------" << tank.pociski[nr].height << " " << tank.pociski[nr].width <<  endl;
				cout << "tank " << tank.x << " " << tank.y << " " << tank.angle << endl;
				cout << "sprite " << sprite.getPosition().x << "  " << sprite.getPosition().y << " " << sprite.getRotation() << endl;
				cout << endl;
				//window.draw(pociska);
			}
			
			sprite.setTexture(tank.texture, false);
			sprite.setPosition(tank.x, tank.y);
			





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
			cout << "jestem!!!!!!!!!!" << endl;
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