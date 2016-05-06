#include "Obiekt.h"
#include <vector>
#include <string>
//*************************************************
//Obiekt -tylko przykladowy do wyslania pól klasy do serwera
//**************************************************
Obiekt::Obiekt()
{
	liczba = 3;
	nazwa = "imie";
	nazwa2 = "nazwisko";
};
//do vectora wrzucamy,  co ma byc wyslane do serwera 
//string - typ przechowywanych danych
//vector przechowuje tylko jeden typ danych, 
//jesli chcemy przeslac int, zamiast stringa, dajemy inta
std::vector<std::string> Obiekt::zwrocNazwe()
{
	std::vector <std::string> zwracane;

	zwracane.push_back(nazwa); //dodaj element nazwa
	zwracane.push_back(nazwa2);

	return zwracane;
};
