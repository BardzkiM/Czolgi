#include "Wykonawcy.h"
#include <SFML/Graphics.hpp>

sf::Font font;
sf::Time delay1 = sf::milliseconds(20);
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

	if (!buffer.loadFromFile("sounds/bomb.wav"))
	{
		std::cerr << "blad czytania dzwieku!" << std::endl;
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
	sound.setBuffer(buffer);
	sound.play();
	for (int i = 0; i < 185; i++)
	{
		window->draw(sprite);
		window->draw(napisy(this->wstep, "Projekt wykonali :", 740, i, true, 52));
		window->display();
		sf::sleep(delay);	
	}
		
	//wjazd z prawej
	sound.play();
	for (int k = 1200; k >=700; k--)
	{
		window->draw(sprite);
		window->draw(napisy(this->wstep, "Projekt wykonali :", 740, 185, true, 52));
		window->draw(napisy(this->wykonawca1, "Michal Bardzki - kierownik", k, 275, false, 45));
		window->display();
		sf::sleep(delay);		
	}

	sound.play();
	for (int k = 1200; k >= 820; k--)
	{
		window->draw(sprite);
		window->draw(napisy(this->wstep, "Projekt wykonali :", 740, 185, true, 52));
		window->draw(napisy(this->wykonawca1, "Michal Bardzki - kierownik", 700, 275, false, 45));
		window->draw(napisy(this->wykonawca2, "Piotr Fic", k, 345, false, 45));
		window->display();
		sf::sleep(delay);
	}

	sound.play();
	for (int k = 1200; k >= 780; k--)
	{
		window->draw(sprite);
		window->draw(napisy(this->wstep, "Projekt wykonali :", 740, 185, true, 52));
		window->draw(napisy(this->wykonawca1, "Michal Bardzki - kierownik", 700, 275, false, 45));
		window->draw(napisy(this->wykonawca2, "Piotr Fic", 820, 345, false, 45));
		window->draw(napisy(this->wykonawca3, "Dominik Pawlik", k, 415, false, 45));//760,415
		window->display();
		sf::sleep(delay);
	}

	sound.play();
	for (int k = 1200; k >= 810; k--)
	{
		window->draw(sprite);
		window->draw(napisy(this->wstep, "Projekt wykonali :", 740, 185, true, 52));
		window->draw(napisy(this->wykonawca1, "Michal Bardzki - kierownik", 700, 275, false, 45));
		window->draw(napisy(this->wykonawca2, "Piotr Fic", 820, 345, false, 45));
		window->draw(napisy(this->wykonawca3, "Dominik Pawlik", 780, 415, false, 45));//760,415
		window->draw(napisy(this->wykonawca3, "Anna Gawor", k, 485, false, 45)); //790,485
		window->display();
		sf::sleep(delay);
	}

	sound.play();
	for (int k = 1200; k >= 780; k--)
	{
		window->draw(sprite);
		window->draw(napisy(this->wstep, "Projekt wykonali :", 740, 185, true, 52));
		window->draw(napisy(this->wykonawca1, "Michal Bardzki - kierownik", 700, 275, false, 45));
		window->draw(napisy(this->wykonawca2, "Piotr Fic", 820, 345, false, 45));
		window->draw(napisy(this->wykonawca3, "Dominik Pawlik", 780, 415, false, 45));//760,415
		window->draw(napisy(this->wykonawca3, "Anna Gawor", 810, 485, false, 45)); //790,485
		window->draw(napisy(this->wykonawca3, "Mikolaj Midura", k, 555, false, 45)); //760,555
		window->display();
		sf::sleep(delay);
	}
	

	window->draw(napisy(this->powrot, "nacisnij klawisz ESCAPE, aby powrócic do menu", 500 , 800, false, 40));
	window->display();
	return 1;
}
