#include "ClientTCP.h"


ClientTCP::~ClientTCP()
{

}

void ClientTCP::Run()
{
	std::cout << "Start w¹tku klienta";
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("192.168.0.5", 53000);
	if (status != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
	char data[100] = { 'c','d','n' };

	// TCP socket:
	if (socket.send(data, 100) != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
}
