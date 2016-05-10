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
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void serialize();
	void deserialize(std::stringstream stream);

	sf::SoundBuffer bufferTank;
	sf::SoundBuffer bufferBullet;
	sf::Sound sound;
	sf::Music music;
	
private:
	std::stringstream mystringstream;
};

#endif