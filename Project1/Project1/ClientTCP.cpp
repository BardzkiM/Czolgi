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
	std::string output_string;
	do
	{
		if (socket.receive(&data, 100, received) != sf::Socket::Done)
		{
			// error...
			//std::cout << "Error during client receiveing";
		}
		std::string temp_string(data);
		output_string = temp_string;
		//std::cout << output_string << std::endl;
	} while (output_string.find("archive")==-1);

	
	std::cout << "Odebrano: " << output_string << std::endl;
	return output_string;
}

void ClientTCP::RunInit()
{
	std::cout << "Start w¹tku klienta" << std::endl;

	sf::Socket::Status status = socket.connect("127.0.0.1", 54000);
	if (status != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
	
	std::string tmp = this->receive();	
	
	std::cout << "[Klient " << tmp << "] before serialize " << tmp << std::endl;
	this->tank->deserialize(tmp);

	
	std::cout << "Klient wszed³ w tryb ci¹g³y" << std::endl;
	while (1)
	{
		this->send(this->tank->serialize());
		this->tank->deserialize(this->receive());
	}

	
}
