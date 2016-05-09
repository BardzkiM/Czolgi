#include "Wykonawcy.h"
#include <SFML/Graphics.hpp>
//#include <Font.hpp>
sf::Font font;
Wykonawcy::Wykonawcy()
{
	//this->position = 1;
	if (!wykonawcy_bg.loadFromFile("images/wykonawcy.bmp"))
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
sf::Text Wykonawcy::napisy(sf::Text text, std::string nazwa, int x, int y, bool style, int size)
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
	
	
	window->draw(napisy(this->wstep, "Projekt wykonali :", 720, 185, true,52));
	window->draw(napisy(this->wykonawca1, "Piotr Fic - kierownik", 720, 275, false,45));
	window->draw(napisy(this->wykonawca2, "Michal Bardzki", 760, 345, false, 45));
	window->draw(napisy(this->wykonawca3, "Dominik Pawlik", 760, 415, false, 45));
	window->draw(napisy(this->wykonawca3, "Anna Gawor", 790, 485, false, 45));
	window->draw(napisy(this->wykonawca3, "Mikolaj Midura", 760, 555, false, 45));
	window->display();
	
	return 1;
}
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(1200, 900), "CZOLGI");
//	Wykonawcy wykonawcy;
//	wykonawcy.set_bg(&window);
//	window.close();
//}