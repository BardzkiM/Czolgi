#include "ClientTCP.h"
#include "Czolg.h"

ClientTCP::ClientTCP(Czolg *source_tank_pointer, sf::Mutex *mutex)
{
	this->tank = source_tank_pointer;
	this->mutex = mutex;
	
}

ClientTCP::~ClientTCP()
{

}
void ClientTCP::deserialize(std::string stream)
{
	std::istringstream archive_istream(stream);
	boost::archive::text_iarchive iarchive(archive_istream);
	iarchive >> this->nr_of_clients;

	//std::cout << "Czolg zostal poprawnie zdeserializowany" << std::endl;
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
	char data[200];
	std::size_t received;
	std::string output_string;
	do
	{
		if (socket.receive(&data, 200, received) != sf::Socket::Done)
		{
			// error...
			std::cout << "Error during client receiveing";
		}
		std::string temp_string(data);
		output_string = temp_string;
		//std::cout <<"[ClientTCP] receive"<< output_string << std::endl;
	} while (output_string.find("archive")==-1);

	
	//std::cout << "Odebrano: " << output_string << std::endl;
	return output_string;
}

void ClientTCP::RunInit()
{
	sf::Time delay_complete_transmission = sf::seconds(0.005);
	std::cout << "Start w�tku klienta" << std::endl;

	sf::Socket::Status status = socket.connect(this->adress, 54000);
	if (status != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
	
	
	this->tank->deserialize(this->receive()); // odbieramy w�asny czo�g przed gr�

	deserialize(this->receive());	//odbieramy liczb� klient�w
	std::cout <<std::endl<< "Klient wszed� w tryb ci�g�y" << std::endl;
	while (1)
	{
		//std::cout << "jestem w �ajlu Klienta  !!!!!!!!!" << nr_of_clients << std::endl;
		this->send(this->tank->serialize());
		this->tank->strzelilem = false;
		for (int i = 0; i < nr_of_clients; i++)
		{
			//std::cout << "[ClientTCP] Przed mutex" << std::endl;
			mutex->lock();
			//std::cout << "[ClientTCP] Po mutex" << std::endl;
			tanks[i].deserialize(this->receive());
			//std::cout << "[ClientTCP] Klient Odebral" << std::endl;
			//std::cout << "[ClientTCP] Po mutex 2" << std::endl;
			mutex->unlock();
			//std::cout << "[ClientTCP] Po mutex 3" << std::endl;
			if (i == tank->nr_czolgu)
			{
				tank->hp = tanks[i].hp;
			}
		}
		
	}

	
}
