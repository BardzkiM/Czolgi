#include "LoadingPage.h"
#include "ServerTCP.h"

LoadingPage::LoadingPage(sf::Thread *server_init)
{
	if (!first_background.loadFromFile("images/second_page_loading_page.png"))
	{
		std::cerr << "blad wczytania pierwszego t³a w menu wyboru!" << std::endl;
		exit(-12);
	}
	if (!second_background.loadFromFile("images/third_page_loading_page.png"))
	{
		std::cerr << "blad wczytania pierwszego t³a w menu wyboru!" << std::endl;
		exit(-12);
	}
	if (!font.loadFromFile("fonts/Bleeding Cowboys.ttf"))
	{
		std::cerr << "blad czytania czcionki do wyswiwtlenia teksu!" << std::endl;
		exit(-12);
	}
	this->server_init = server_init;
}
LoadingPage::~LoadingPage()
{

}

sf::Text LoadingPage::napisy(sf::Text text, std::string nazwa, float x, float y, bool style, int size)
{
	text.setFont(font);
	text.setString(nazwa);
	text.setPosition(x, y);//10,30
	text.setCharacterSize(size);
	text.setColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);

	if (style == true)
		text.setStyle(sf::Text::Italic);

	return text;
}

std::string LoadingPage::run(sf::RenderWindow *window)
{
	sf::String adress;
	bool is_server_running = false;
	
	sf::Time delay_after_first_page = sf::seconds(1.4);
	sf::Time delay_after_character = sf::seconds(0.2);

	window->setKeyRepeatEnabled(false); //przycisk siê wciœnie tylko raz, nawet jak trzymamy

	window->clear();
	sf::Sprite sprite1(this->first_background);
	window->draw(sprite1);
	window->display();
	sf::sleep(delay_after_first_page);
	sf::Sprite sprite2(this->second_background);
	window->draw(sprite2);	
	window->draw(napisy(this->text, "", 490, 202, true, 52));
	window->display();

	while (1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			adress += "0";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			adress += "1";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			adress += "2";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			adress += "3";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			adress += "4";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			adress += "5";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		{
			adress += "6";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
		{
			adress += "7";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
		{
			adress += "8";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
		{
			adress += "9";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
		{
			adress += ".";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			adress = adress.substring(0,adress.getSize()-1);
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !is_server_running)
		{
			server_init->launch();
			is_server_running = true;			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			return adress;
		}

		
	}	
}