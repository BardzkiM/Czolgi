#include "Wykonawcy.h"
#include <SFML/Graphics.hpp>

sf::Font font;
sf::Time delay = sf::milliseconds(2);
Wykonawcy::Wykonawcy()
{
	
	if (!wykonawcy_bg.loadFromFile("images/wykonawcy.png"))
	{
		std::cerr << "blad czytania tla wykonawcy!" << std::endl;
		exit(-12);
	}

	// Load font from a file
	if (!font.loadFromFile("fonts/shlop.ttf"))
	{
		std::cerr << "blad czytania czcionki do wyswiwtlenia teksu!" << std::endl;
		exit(-12);
	}

}
Wykonawcy::~Wykonawcy()
{

}
sf::Text Wykonawcy::napisy(sf::Text text, std::string nazwa, float x, float y, bool style, int size)
{
	text.setFont(font);
	text.setString(nazwa);
	text.setPosition(x,y);//10,30
	text.setCharacterSize(size);
	text.setColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	
	if(style==true)
		text.setStyle(sf::Text:: Italic);

	return text;
}
int Wykonawcy::set_bg(sf::RenderWindow *window)
{

	window->clear();
	sf::Sprite sprite(wykonawcy_bg);
	window->draw(sprite);
	window->display();

	//zjazd od góry
	for (int i = 0; i < 185; i++)
	{
		window->draw(sprite);
		window->draw(napisy(this->wstep, "Projekt wykonali :", 720, i, true, 52));
		window->display();
		sf::sleep(delay);		
	}
	
	//wjazd z prawej
	for (int k = 1200; k >=720; k--)
	{
		window->draw(sprite);
		window->draw(napisy(this->wstep, "Projekt wykonali :", 720, 185, true, 52));
		window->draw(napisy(this->wykonawca1, "Piotr Fic - kierownik", k, 275, false, 45));
		window->display();
		sf::sleep(delay);		
	}

	for (int k = 1200; k >= 760; k--)
	{
		window->draw(sprite);
		window->draw(napisy(this->wstep, "Projekt wykonali :", 720, 185, true, 52));
		window->draw(napisy(this->wykonawca1, "Piotr Fic - kierownik", 720, 275, false, 45));
		window->draw(napisy(this->wykonawca2, "Michal Bardzki", k, 345, false, 45));
		window->display();
		sf::sleep(delay);
	}

	for (int k = 1200; k >= 760; k--)
	{
		window->draw(sprite);
		window->draw(napisy(this->wstep, "Projekt wykonali :", 720, 185, true, 52));
		window->draw(napisy(this->wykonawca1, "Piotr Fic - kierownik", 720, 275, false, 45));
		window->draw(napisy(this->wykonawca2, "Michal Bardzki", 760, 345, false, 45));
		window->draw(napisy(this->wykonawca3, "Dominik Pawlik", k, 415, false, 45));//760,415
		window->display();
		sf::sleep(delay);
	}

	for (int k = 1200; k >= 790; k--)
	{
		window->draw(sprite);
		window->draw(napisy(this->wstep, "Projekt wykonali :", 720, 185, true, 52));
		window->draw(napisy(this->wykonawca1, "Piotr Fic - kierownik", 720, 275, false, 45));
		window->draw(napisy(this->wykonawca2, "Michal Bardzki", 760, 345, false, 45));
		window->draw(napisy(this->wykonawca3, "Dominik Pawlik", 760, 415, false, 45));//760,415
		window->draw(napisy(this->wykonawca3, "Anna Gawor", k, 485, false, 45)); //790,485
		window->display();
		sf::sleep(delay);
	}

	for (int k = 1200; k >= 760; k--)
	{
		window->draw(sprite);
		window->draw(napisy(this->wstep, "Projekt wykonali :", 720, 185, true, 52));
		window->draw(napisy(this->wykonawca1, "Piotr Fic - kierownik", 720, 275, false, 45));
		window->draw(napisy(this->wykonawca2, "Michal Bardzki", 760, 345, false, 45));
		window->draw(napisy(this->wykonawca3, "Dominik Pawlik", 760, 415, false, 45));//760,415
		window->draw(napisy(this->wykonawca3, "Anna Gawor", 790, 485, false, 45)); //790,485
		window->draw(napisy(this->wykonawca3, "Mikolaj Midura", k, 555, false, 45)); //760,555
		window->display();
		sf::sleep(delay);
	}
	
	return 1;
}
