#include "Menu.h"

Menu::Menu()
{
	this->position = 1;
	if (!menu_bg.loadFromFile("images/menu_bg.jpg"))
	{
		std::cerr<< "blad czytania mapy" << std::endl;
		exit(-12);
	}
		

	if (!buffer.loadFromFile("sounds/menuOption.wav"))
	{
		std::cerr << "blad czytania dzwieku!" << std::endl;
		exit(-12);
	}
	sound.setBuffer(buffer);
}

Menu::~Menu()
{

}

void Menu::key_up(sf::RenderWindow *window)
{

	if (this->position == 1)
	{
		this->position = 3;
	}
	else {
		this->position--;
	}
	sound.play();
	this->set_auto_menu_pos(window);
}
void Menu::key_down(sf::RenderWindow *window)
{
	if (this->position == 3)
	{
		this->position = 1;
	}
	else
	{
		this->position++;
	}
	sound.play();
	this->set_auto_menu_pos(window);
}

int Menu::set_bg(sf::RenderWindow *window)
{
	
	sf::Sprite sprite(menu_bg);
	window->draw(sprite);
	//music.play();
	return 1;
}

int Menu::set_menu_pos_1(sf::RenderWindow *window)
{
	//window->clear();

	sf::Sprite sprite(menu_bg);
	window->draw(sprite);
	if (!menu_bg_bullets.loadFromFile("images/bullets1.png"))
	{
		return EXIT_FAILURE;
	}
	sf::Sprite sprite1(menu_bg_bullets);
	window->draw(sprite1);
	window->display();
	
	return 1;
}

int Menu::set_menu_pos_2(sf::RenderWindow *window)
{
	//window->clear();

	sf::Sprite sprite(menu_bg);
	window->draw(sprite);
	if (!menu_bg_bullets.loadFromFile("images/bullets2.png"))
	{
		return EXIT_FAILURE;
	}
	sf::Sprite sprite1(menu_bg_bullets);
	window->draw(sprite1);
	window->display();
	
	return 1;
}

int Menu::set_menu_pos_3(sf::RenderWindow *window)
{
	//window->clear();
	sf::Sprite sprite1(menu_bg);
	window->draw(sprite1);
	if (!menu_bg_bullets.loadFromFile("images/bullets3.png"))
	{
		return EXIT_FAILURE;
	}
	sf::Sprite sprite(menu_bg_bullets);
	window->draw(sprite);
	window->display();
	
	return 1;
}

int Menu::set_auto_menu_pos(sf::RenderWindow *window)
{
	//window->clear();
	switch (this->position)
	{
	case 1:
	{
		set_menu_pos_1(window);
		break;
	}
	case 2:
	{
		set_menu_pos_2(window);
		break;
	}
	case 3:
	{
		set_menu_pos_3(window);
		break;
	}
	default:
		return 1;
	}
}