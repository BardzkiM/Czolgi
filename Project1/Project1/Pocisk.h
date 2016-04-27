#pragma once
#include "Blok.h"
#ifndef Pocisk_h
#define Pocisk_h
class Pocisk : public Blok
{
public:
	Pocisk();
	~Pocisk();
	int id_czolgu;
	float speed;
	char type;
};
#endif
