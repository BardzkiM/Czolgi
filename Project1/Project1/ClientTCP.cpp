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
using namespace std;
std::string ClientTCP::receive()
{
	char data[1500];
	std::size_t received;
	std::string output_string;
	do
	{
		cout << "::BEGIN SOCKET.RECEIVE::" << endl;
		if (socket.receive(&data, 1500, received) != sf::Socket::Done)
		{
			// error...
			//std::cout << "Error during client receiveing";
		}
		cout << "::END SOCKET>RECEIVE::" << endl;
		std::string temp_string(data);
		output_string = temp_string;
		//std::cout << output_string << std::endl;
		std::cout <<"RECIEVE"<< (output_string.find("archive") == -1) << std::endl;
	} while (output_string.find("archive")==-1);

	
	//std::cout << "Odebrano: " << output_string << std::endl;
	return output_string;
}

void ClientTCP::RunInit()
{
	std::cout << "Start w¹tku klienta" << std::endl;

	sf::Socket::Status status = socket.connect(this->adress, 54000);
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
		cout << "::WHILE BEGIN::" << endl;
		//std::cout << "jestem w ³ajlu Klienta  !!!!!!!!!" << nr_of_clients << std::endl;
		this->send(this->tank->serialize());
		this->tank->strzelilem = false;
		std::cout << nr_of_clients << std::endl;
		for (int i = 0; i < nr_of_clients; i++)
		{
			cout << "::FOR BEGIN::" << endl;
			//std::cout << "[ClientTCP] Przed mutex" << std::endl;
			//mutex->lock();
			//std::cout << "[ClientTCP] Po mutex" << std::endl;
			
			string _receive = this->receive();
			cout << "::READ REC:: "<< _receive << endl;
			tanks[i].deserialize(_receive);
			cout << "::DESERIALIZE REC::" << endl;
			//std::cout << "[ClientTCP] Klient Odebral" << std::endl;
			//std::cout << "[ClientTCP] Po mutex 2" << std::endl;
			//mutex->unlock();
			//std::cout << "[ClientTCP] Po mutex 3" << std::endl;
			std::cout <<"AAAAAAAAAAAAAAAAAAAAAAAAAAAA: "<< i<<": "<< tank->nr_czolgu <<": "<< tanks[i].x << std::endl;
			if (i == tank->nr_czolgu)
			{
				tank->hp = tanks[i].hp;
			}
			std::cout << "::FOR END::" << nr_of_clients << std::endl;
		}
		cout << "::WHILE END::" << endl;
	}
	std::cout << "WHILE OUT" << std::endl;

	
}
