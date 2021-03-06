#pragma once
#include "Pocisk.h"
#include "Blok.h"
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_member.hpp>
#include <sstream>
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "GraDane.h"
#ifndef _CZOLG_H
#define _CZOLG_H
class Czolg : public Blok
{
public:
	Czolg();
	~Czolg();
	std::vector <Pocisk> pociski;
	void addPocisk();
	void removePocisk(int j);
	void setInitialPosition(int x, int y);
	void move(int x, int y);
	std::string serialize();
	void deserialize(std::string stream);
	void deserializeForServer(std::string stream);
	void sprawdzKolizjePociskowPrzeszkod();
	bool sprawdzKolizjeCzolgPrzeszkoda();
	int nr_czolgu = -1;
	bool strzelilem = false;
	void setBar();

	sf::Texture textureBar;
	sf::Texture textureBar1;
	sf::Texture textureBar2;
	sf::Texture textureBar3;
	sf::Texture textureBar4;

	sf::SoundBuffer bufferTank;
	sf::SoundBuffer bufferBullet;
	sf::Sound sound;
	sf::Music music;

	sf::Sprite hpBar;
	
private:

	std::stringstream mystringstream;

};

#endif