#include "SFML\Network.hpp"

/*
sf::TcpSocket socket; // tworzymy gniazdo klienta
sf::IpAddress ip = sf::IpAddress::LocalHost;// "adres.ip.serwera.do.ktorego.sie.chcesz.polaczyc";
unsigned int port = 54000; // port na kt�rym nas�uchuje serwer

if (socket.connect(ip, port) != sf::Socket::Done) // ��czymy si� z adresem 'ip' na porcie 'port'
// je�li funkcja connect zwr�ci sf::Socket::Done oznacza to, �e wszystko posz�o dobrze
{
cerr << "Nie mo�na po��czy� si� z " << ip.toString() << endl;
exit(1);
}
else
{
	cerr << "Jestem klientem, w�a�nie nawi�za�em po��czenie z serwerem";
	exit(1);
}
*/