#include "Wykonawcy.h"

Wykonawcy::Wykonawcy()
{
	//this->position = 1;
	if (!wykonawcy_bg.loadFromFile("images/wykonawcy.bmp"))
	{
		std::cerr << "blad czytania tla wykonawcy!" << std::endl;
		exit(-12);
	}
	this->wstep.setString("Projekt wykonali:");
	this->wykonawca1.setString("Piotr Fic - kierownik");
	this->wykonawca2.setString("Micha³ Bardzki");
	this->wykonawca3.setString("Dominik Pawlik");
	this->wykonawca4.setString("Anna Gawor");
	this->wykonawca5.setString("Miko³aj Midura");
}
Wykonawcy::~Wykonawcy()
{

}
sf::Text Wykonawcy::napisy(sf::Text text, std::string nazwa, int x, int y)
{
	text.setString(nazwa);
	text.setPosition(x,y);//10,30
	text.setCharacterSize(20);
	text.setColor(sf::Color::Red);

	return text;
}
int Wykonawcy::set_bg(sf::RenderWindow *window)
{
	//napisy(this->wstep, "Projekt",10,30);
	sf::Sprite sprite(wykonawcy_bg);
	
	window->draw(sprite);
	//window->display();
	window->draw(napisy(this->wstep, "Projekt", 100, 300));
	window->display();
	
	return 1;
}