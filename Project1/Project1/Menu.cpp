#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include "Czolg.h"

class Menu
{
public:
	Menu();
	~Menu();

	int set_bg(sf::RenderWindow * window);

	

private:
	sf::Texture menu_bg;
};

Menu::Menu()
{
}

Menu::~Menu()
{
}

int Menu::set_bg(sf::RenderWindow *window)
{
	if (!menu_bg.loadFromFile("menu_bg.jpg"))
	{
		return EXIT_FAILURE;
	}
	sf::Sprite sprite(menu_bg);
	window->draw(sprite);
}

