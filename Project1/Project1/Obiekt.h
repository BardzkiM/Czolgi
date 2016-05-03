#pragma once
#ifndef _OBIEKT_H
#define _OBIEKT_H
#include <string>
#include <vector>

//Obiekt -tylko przykladowy do wyslania pól klasy do serwera
class Obiekt
{
public:
	int liczba;
	std::string nazwa;
	std::string nazwa2;
	Obiekt();
	std::vector<std::string> zwrocNazwe();
};
#endif // !_OBIEKT_H