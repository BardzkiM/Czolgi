#pragma once
#include "Pocisk.h"
#include "Blok.h"
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_member.hpp>
#include <sstream>
#include "SFML/Graphics.hpp"
#ifndef _CZOLG_H
#define _CZOLG_H
class Czolg : public Blok
{
public:
	Czolg();
	~Czolg();
	std::vector <Pocisk> pociski;
	void addPocisk();
	void setInitialPosition(int x, int y);
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void serialize();
	void deserialize(std::stringstream stream);
	
private:
	std::stringstream mystringstream;
};

#endif