#include "ClientTCP.h"
#include "Czolg.h"

ClientTCP::ClientTCP(Czolg *source_tank_pointer)
{
	this->tank = source_tank_pointer;
}

ClientTCP::~ClientTCP()
{

}
void ClientTCP::deserialize(std::string stream)
{
	std::istringstream archive_istream(stream);
	boost::archive::text_iarchive iarchive(archive_istream);
	iarchive >> this->nr_of_clients;

	std::cout << "Czolg zostal poprawnie zdeserializowany" << std::endl;
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

	sf::Socket::Status status = socket.connect("127.0.0.0", 54000);
	if (status != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
	
	
	this->tank->deserialize(this->receive()); // odbieramy w³asny czo³g przed gr¹

	deserialize(this->receive());	//odbieramy liczbê klientów
	std::cout <<std::endl<< "Klient wszed³ w tryb ci¹g³y" << std::endl;
	while (1)
	{
		std::cout << "jestem w ³ajlu Klienta  !!!!!!!!!" << nr_of_clients << std::endl;
		this->send(this->tank->serialize());
		for (int i = 0; i < nr_of_clients; i++)
		{
		
			tanks[i].deserialize(this->receive());
		}
	}

	
}
