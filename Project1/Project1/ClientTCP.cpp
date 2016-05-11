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
	std::cout << "Start w¹tku klienta" << std::endl;

	sf::Socket::Status status = socket.connect("127.0.0.1", 54000);
	if (status != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
	std::cout << "jestem";
	std::string tmp = this->receive();
	numer_klienta = this->receive();
	std::string tmp2 = this->receive();


	std::cout << "[Klient " << numer_klienta << "] before serialize " << tmp << std::endl;
	this->tank->deserialize(tmp);

	//GraDane::iloscGraczy = atoi(this->receive().c_str());
	//std::cout << GraDane::iloscGraczy << std::endl;
	//socket.
	//std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!" << socket.isBlocking() << std::endl;

	char data[100];
	std::size_t received;
	sf::Socket::Status tmp_soc = socket.receive(&data, 100, received);

	while (tmp_soc == sf::Socket::Status::NotReady);
	{
		std::cout << "jeje!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << std::endl;
		tmp_soc = socket.receive(&data, 100, received);
	}





	//if (socket.receive(&data, 100, received) == sf::Socket::NotReady)
	//{
		// error...
	//	std::cout << "Error during client receiveing";
	//}

	std::string output_string(data);
	std::cout << "Odebrano: " << numer_klienta << "---   " << output_string << std::endl;
	std::cout << "[Klient " << numer_klienta << "] before serialize " << tmp2 << std::endl;

	//std::cout << receive().c_str() << std::endl;
}
