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
	
	std::string test = czolg.serialize();
	
	if (socket.send(test.c_str(),test.length()+1) != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
	std::size_t received;

	if (socket.receive(&data, 100, received) != sf::Socket::Done)
	{
		// error...
		std::cout << "Error during client receiveing";
	}

	std::cout << "Klient odebra³ wiadomoœæ: " << data << " , rozmiar wiadomoœci " << received << " bajty";
}
