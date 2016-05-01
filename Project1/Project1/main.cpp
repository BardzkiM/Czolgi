#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include "Czolg.h"
/*

using namespace std;

int main()
{
	
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
	sf::Sprite tank_sprite(tank.texturel);
	sf::Sprite pociska;
	tank.setInitialPosition(100,100);
	tank_sprite.setPosition(tank.x- tank.width/2, tank.y - tank.height / 2);


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

				pociska.setTexture(tank.pociski[nr].texture);
				pociska.setPosition(tank.pociski[nr].x, tank.pociski[nr].y);

				//pociska.rotate(tank.pociski[nr].angle);

				cout << "pocisk " << tank.pociski[nr].x << " " << tank.pociski[nr].y <<" " << tank.pociski[nr].angle << "----------" << tank.pociski[nr].height << " " << tank.pociski[nr].width <<  endl;
				cout << "tank " << tank.x << " " << tank.y << " " << tank.angle << endl;
				cout << "tank_sprite " << tank_sprite.getPosition().x << "  " << tank_sprite.getPosition().y << " " << tank_sprite.getRotation() << endl;
				cout << endl;
				//window.draw(pociska);
			}
			
			tank_sprite.setTexture(tank.texture);
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
		// Draw the tank_sprite
		window.draw(tank_sprite);
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
		//window.draw(tank_spriteImage);
		//window.clear();
		//window.draw(shape);
		//window.display();
	}
	return EXIT_SUCCESS;

	//return 0;
}*/