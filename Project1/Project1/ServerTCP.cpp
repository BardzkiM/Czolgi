#include "ServerTCP.h"
ServerTCP::ServerTCP()
{

}

ServerTCP::~ServerTCP()
{

}

void ServerTCP::Run()
{
	std::cout << "Start w¹tku servera"<<argument;
	sf::TcpListener listener; // tworzymy gniazdo nas³uchujace
	unsigned int port = 54000; // port, na którym bêdziemy nas³uchiwaæ

	if (listener.listen(port) != sf::Socket::Done) // rozpoczynamy nas³uchiwanie na porcie 'port'
	{
		std::cerr << "Nie mogê rozpocz¹æ nas³uchiwania na porcie " << port << std::endl;
		exit(1);
	}

	// accept a new connection
	sf::TcpSocket client;
	if (listener.accept(client) != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
	//char data[100];
	//std::size_t received;

	//// TCP socket:
	//if (client.receive(data, 100, received) != sf::Socket::Done)
	//{
	//	// error...
	//	std::cout << "error";
	//}
	//std::cout << "Received " << received << " bytes" << std::endl;
}

