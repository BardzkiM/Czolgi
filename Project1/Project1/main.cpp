#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>


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


	/////obraz///////////
	sf::Texture texture;
	if (!texture.loadFromFile("tank.png"))
	{
		cout << "nie mo¿na za³adowaæ pliku" << endl;
		return EXIT_FAILURE;
	}
	sf::Sprite sprite(texture);

	sf::Vector2u movement(10, 10);




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
				if (sprite.getRotation() == 0)
				{
					sprite.move(-5, 0);
				}
				if (sprite.getRotation() == 90)
				{
					sprite.move(0, -5);
				}
				if (sprite.getRotation() == 180)
				{
					sprite.move(5, 0);
				}
				if (sprite.getRotation() == 270)
				{
					sprite.move(0, 5);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (sprite.getRotation() == 0)
				{
					sprite.move(5, 0);
				}
				if (sprite.getRotation() == 90)
				{
					sprite.move(0, 5);
				}
				if (sprite.getRotation() == 180)
				{
					sprite.move(-5, 0);
				}
				if (sprite.getRotation() == 270)
				{
					sprite.move(0, -5);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				//sprite.move(30,0);
				sprite.setRotation(sprite.getRotation() + 90);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				//sprite.move(-30, 0);
				sprite.setRotation(sprite.getRotation() - 90);
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