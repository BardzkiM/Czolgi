#include "ClientTCP.h"
#include "Czolg.h"

ClientTCP::ClientTCP()
{

}

ClientTCP::~ClientTCP()
{

}

void ClientTCP::Run()
{
	std::cout << "Start w¹tku klienta"<< std::endl;
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("127.0.0.1", 54000);
	if (status != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
	char data[100] = { 'c','d','n' };
	Czolg czolg;
	// TCP socket:
	sf::Packet pakiet;
	pakiet.append(&czolg, sizeof(czolg));
	
	if (socket.send(data, 100) != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
}
