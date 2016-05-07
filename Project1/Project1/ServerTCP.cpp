#include "ServerTCP.h"
ServerTCP::ServerTCP()
{

}

ServerTCP::~ServerTCP()
{

}

void ServerTCP::accept_client()
{
	std::cout << "Oczekiwanie na akceptacjê klienta";
		nr_of_clients++;
		sf::TcpSocket *temp = new sf::TcpSocket[nr_of_clients];
		//std::copy(client, client + (nr_of_clients - 1), temp);
		memcpy(temp,client,nr_of_clients-1);
		delete[] client;
		client = temp;
		if (listener.accept(client[nr_of_clients - 1]) != sf::Socket::Done)
		{
			// error...
			std::cout << "error";
		}
		this->receive(nr_of_clients-1);
		
		
	
}

void ServerTCP::receive(int which_client)
{
	char data[100];
	std::size_t received;

	// TCP socket:
	if (client[which_client].receive(data, 100, received) != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
	std::cout << "Received " << received << " bytes" << data << std::endl;
}

void ServerTCP::Run()
{
	std::cout << "Start w¹tku servera"<<argument;
	//sf::TcpListener listener; // tworzymy gniazdo nas³uchujace
	unsigned int port = 54000; // port, na którym bêdziemy nas³uchiwaæ

	if (listener.listen(port) != sf::Socket::Done) // rozpoczynamy nas³uchiwanie na porcie 'port'
	{
		std::cerr << "Nie mogê rozpocz¹æ nas³uchiwania na porcie " << port << std::endl;
		exit(1);
	}
	this->accept_client();
	sf::Thread oczekiwanie_na_nastepnego_klienta(&ServerTCP::accept_client, this);
	oczekiwanie_na_nastepnego_klienta.launch();

	/*this->receive(0);*/
	//this->receive(1);
	// accept a new connection
	//sf::TcpSocket client;
	//if (listener.accept(client) != sf::Socket::Done)
	//{
	//	// error...
	//	std::cout << "error";
	//}
	//char data[100];
	//std::size_t received;

	//// TCP socket:
	//if (client[0].receive(data, 100, received) != sf::Socket::Done)
	//{
	//	// error...
	//	std::cout << "error";
	//}
	//std::cout << "Received " << received << " bytes" << data << std::endl;
}

