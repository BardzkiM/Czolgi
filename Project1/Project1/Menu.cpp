#include "Menu.h"

Menu::Menu()
{

}

Menu::~Menu()
{

}

int Menu::set_bg(sf::RenderWindow *window)
{
	if (!menu_bg.loadFromFile("images/menu_bg1.jpg"))
	{
		return EXIT_FAILURE;
	}
	sf::Sprite sprite(menu_bg);
	window->draw(sprite);
	return 1;
}

