#include "Blok.h"


Blok::Blok()
{
}


Blok::~Blok()
{
}

void Blok::setRotation()
{
	switch (this->angle)
	{
		case 0:
			texture = texturel;
			break;
		case 90:
			texture = textureu;
			break;
		case 180:
			texture = texturer;
			break;
		case 270:
			texture = textured;
			break;
	}
}