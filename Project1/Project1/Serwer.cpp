#include "SFML\Network.hpp"
/*
sf::TcpListener listener; // tworzymy gniazdo nas³uchujace
unsigned int port = 54000; // port, na którym bêdziemy nas³uchiwaæ

if (listener.listen(port) != sf::Socket::Done) // rozpoczynamy nas³uchiwanie na porcie 'port'
{
	cerr << "Nie mogê rozpocz¹æ nas³uchiwania na porcie " << port << endl;
	exit(1);
}
else
{
	cerr << "Jestem serwerem, w³aœnie nawi¹za³em po³¹czenie z klientem";
		exit(1);
}*/
/*
sf::TcpListener listener; //nasz "nasluchiwacz"
if (!listener.listen(43333))
{
	cout << "Nie mozna nasluchiwac na porcie 43333" << endl;
	return 1;
}
sf::TcpSocket clientSocket;
listener.accept(clientSocket);
sf::Packet pack;
pack << std::string("Witam! Tu SERVER");
clientSocket.send(pack);
pack.clear();
clientSocket.receive(pack);
std::string wiadomosc;
if (pack >> wiadomosc)
{
	cout << "Nie mozna wypakowac wiadomosci z pakietu!" << endl;
}
else cout << "Client: " << wiadomosc << endl;
*/