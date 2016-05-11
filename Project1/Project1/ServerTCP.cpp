#include "ServerTCP.h"
#include "Czolg.h"
#include "GraDane.h"
ServerTCP::ServerTCP()
{
	tank[0].setInitialPosition(0, 0);
	tank[1].setInitialPosition(1140, 840);
	tank[2].setInitialPosition(0, 840);
	tank[3].setInitialPosition(1140, 0);
}

ServerTCP::~ServerTCP()
{

}

void ServerTCP::accept_client()
{
	std::cout << "Oczekiwanie na akceptacj� klienta"<< std::endl;
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
		//this->receive(nr_of_clients-1);	
}

void ServerTCP::send(int which_client, std::string message)
{
	if (client[which_client].send(message.c_str(), message.length() + 1) != sf::Socket::Done)
	{
		std::cout << "Bl�d wysy�ania do klienta";
	}
}

void ServerTCP::receive(int which_client)
{
	char data[100];
	
	std::size_t received;
	

	// TCP socket:

	if (client[which_client].receive(&data,100,received) != sf::Socket::Done)
	{
		// error...
		std::cout << "error";
	}
	std::string	received_data_str(data);			//tworzymy nowy string na podstawie tablicy char�w
	Czolg czolg_test;								//tworzymy testowy obiekt czolg
	czolg_test.deserialize(received_data_str);		//deserializujemy obiekt (czyli wczytujemy spowrotem wszystkie dane dla niego niezb�dne)
	
	std::cout << "Received " << received <<  " bytes" << " " << received_data_str << std::endl;
}

void ServerTCP::RunInit()
{
	std::cout << std::endl << "Start w�tku servera "<< argument << std::endl;
	//sf::TcpListener listener; // tworzymy gniazdo nas�uchujace
	unsigned int port = 54000; // port, na kt�rym b�dziemy nas�uchiwa�

	if (listener.listen(port) != sf::Socket::Done) // rozpoczynamy nas�uchiwanie na porcie 'port'
	{
		std::cerr << "Nie mog� rozpocz�� nas�uchiwania na porcie " << port << std::endl;
		exit(1);
	}
	const int clients_size = 4;
	sf::Thread *clients[clients_size];
	


	for (int i = 0; i < 2; i++)
	{
		clients[i] = new sf::Thread(&ServerTCP::accept_client, this);
		clients[i]->launch();
		clients[i]->wait();
		std::cout << " Po��czono z klientem " << i << " [SERVER]" << std::endl;
		this->send(i, tank[i].serialize());	
		
	}
	int k;
	std::cin >> k;
	std::cout << "podano k" << std::endl;
	for (int i = 0; i < nr_of_clients; i++)
	{
		this->send(i, std::to_string(nr_of_clients));
	}
	//sf::Thread client_1(&ServerTCP::accept_client, this);
}
void ServerTCP::runGame()
{
	
		
		//this->send(0, std::to_string(nr_of_clients - 1));
	
}
