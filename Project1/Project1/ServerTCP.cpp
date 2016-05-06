#include "ServerTCP.h"
ServerTCP::ServerTCP()
{

}

ServerTCP::~ServerTCP()
{

}


void ServerTCP::server_creation()
{
	sf::TcpListener listener;

	// bind the listener to a port
	if (listener.listen(53000) != sf::Socket::Done)
	{
		// error...
	}

	// accept a new connection
	sf::TcpSocket client;
	if (listener.accept(client) != sf::Socket::Done)
	{
		// error...
	}
	char data[100];
	std::size_t received;

	// TCP socket:
	if (client.receive(data, 100, received) != sf::Socket::Done)
	{
		// error...
	}
	std::cout << "Received " << received << " bytes" << std::endl;
}

void ServerTCP::client_connection()
{
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("192.168.0.5", 53000);
	if (status != sf::Socket::Done)
	{
		// error...
	}
	char data[100] = { 'c','d','n' };

	// TCP socket:
	if (socket.send(data, 100) != sf::Socket::Done)
	{
		// error...
	}
}
