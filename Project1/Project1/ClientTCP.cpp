#include "ClientTCP.h"
#include "Czolg.h"

ClientTCP::ClientTCP(Czolg *source_tank_pointer)
{
	this->tank = source_tank_pointer;
}

ClientTCP::~ClientTCP()
{

}

void ClientTCP::send(std::string message)
{
	if (socket.send(message.c_str(), message.length() + 1) != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
}

std::string ClientTCP::receive()
{
	char data[100];
	std::size_t received;
	if (socket.receive(&data, 100, received) != sf::Socket::Done)
	{
		// error...
		std::cout << "Error during client receiveing";
	}

	std::string output_string(data);
	std::cout << "Odebrano: " << output_string << std::endl;
	return output_string;
}

void ClientTCP::RunInit()
{
	sf::SocketSelector selector;
	std::cout << "Start w¹tku klienta"<< std::endl;
	
	sf::Socket::Status status = socket.connect("127.0.0.1", 54000);
	selector.add(socket);
	if (status != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}	
	std::cout << "jestem";
	std::string tmp = this->receive();
	std::cout << tmp;
	this->tank->deserialize(tmp);
	socket.setBlocking(false);
	//GraDane::iloscGraczy = atoi(this->receive().c_str());
	//std::cout << GraDane::iloscGraczy << std::endl;
	//socket.
	//std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!" << socket.isBlocking() << std::endl;
	
	char data[100];
	std::size_t received;
	sf::Socket::Status tmp_soc;
	
do 
	{
		tmp_soc = socket.receive(&data, 100, received);
	} while (tmp_soc == sf::Socket::Status::NotReady);
	




	//if (socket.receive(&data, 100, received) == sf::Socket::NotReady)
	//{
		// error...
	//	std::cout << "Error during client receiveing";
	

	std::string output_string(data);
	std::cout << "Odebrano: " << output_string << std::endl;

	//std::cout << receive().c_str() << std::endl;
}
