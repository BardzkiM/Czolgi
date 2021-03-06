#include "LoadingPage.h"
#include "ServerTCP.h"


LoadingPage::LoadingPage(sf::Thread *server_init, sf::Thread *server_game, sf::Thread *client_tcp_thread, ClientTCP *client_tcp)
{
	if (!first_background.loadFromFile("images/second_page_loading_page.png"))
	{
		std::cerr << "blad wczytania pierwszego t�a w menu wyboru!" << std::endl;
		exit(-12);
	}
	if (!second_background.loadFromFile("images/third_page_loading_page.png"))
	{
		std::cerr << "blad wczytania pierwszego t�a w menu wyboru!" << std::endl;
		exit(-12);
	}
	if (!font.loadFromFile("fonts/Bleeding Cowboys.ttf"))
	{
		std::cerr << "blad czytania czcionki do wyswiwtlenia teksu!" << std::endl;
		exit(-12);
	}
	this->server_init = server_init;
	this->server_game = server_game;
	this->client_tcp_thread = client_tcp_thread;
	this->client_tcp = client_tcp;
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
	sf::String adress = "127.0.0.1";
	bool is_server_running = false;
	bool does_user_type_anything = false;

	sf::Time delay_after_first_page = sf::seconds(0.3);
	sf::Time delay_after_character = sf::seconds(0.18);

	window->setKeyRepeatEnabled(false); //przycisk si� wci�nie tylko raz, nawet jak trzymamy

	window->clear();
	sf::Sprite sprite1(this->first_background);
	window->draw(sprite1);
	window->display();
	sf::sleep(delay_after_first_page);
	sf::Sprite sprite2(this->second_background);
	window->draw(sprite2);	
	window->draw(napisy(this->text, adress, 490, 202, true, 52));
	window->display();	
	while (1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			if (!does_user_type_anything)
			{
				adress = "";
				does_user_type_anything = true;
			}

			adress += "0";//"127.0.0.1";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			if (!does_user_type_anything)
			{
				adress = "";
				does_user_type_anything = true;
			}
			adress += "1";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			if (!does_user_type_anything)
			{
				adress = "";
				does_user_type_anything = true;
			}
			adress += "2";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			if (!does_user_type_anything)
			{
				adress = "";
				does_user_type_anything = true;
			}
			adress += "192.168.43.142";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			if (!does_user_type_anything)
			{
				adress = "";
				does_user_type_anything = true;
			}
			adress +="192.168.43.95";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			if (!does_user_type_anything)
			{
				adress = "";
				does_user_type_anything = true;
			}
			adress += "5";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		{
			if (!does_user_type_anything)
			{
				adress = "";
				does_user_type_anything = true;
			}
			adress += "6";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
		{
			if (!does_user_type_anything)
			{
				adress = "";
				does_user_type_anything = true;
			}
			adress += "7";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
		{
			if (!does_user_type_anything)
			{
				adress = "";
				does_user_type_anything = true;
			}
			adress += "8";//"192.168.1.8";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
		{
			if (!does_user_type_anything)
			{
				adress = "";
				does_user_type_anything = true;
			}
			adress += "9";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
		{
			if (!does_user_type_anything)
			{
				adress = "";
				does_user_type_anything = true;
			}
			adress += ".";
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			if (!does_user_type_anything)
			{
				adress = "";
				does_user_type_anything = true;
			}
			adress = adress.substring(0,adress.getSize()-1);
			window->draw(sprite2);
			window->draw(napisy(this->text, adress, 490, 202, true, 52));
			window->display();
			sf::sleep(delay_after_character);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (is_server_running)
			{
				server_init->terminate();
				server_game->launch();
				sf::sleep(delay_after_character);
			}
			if (!is_server_running)
			{
				server_init->launch();
				is_server_running = true;
				sf::sleep(delay_after_character);
			}
			
						
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if (is_server_running == true)
			{
				client_tcp->adress = adress;
				client_tcp_thread->launch();
				sf::Time delay_after_client_connection = sf::seconds(0.3);
				sf::sleep(delay_after_client_connection);
				server_init->terminate();
				server_game->launch();
			}
			else
			{
				client_tcp->adress = adress;
				client_tcp_thread->launch();
			}
			return adress;
		}

		
	}	
}