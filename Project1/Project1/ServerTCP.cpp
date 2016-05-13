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
		//sf::TcpSocket *temp = new sf::TcpSocket[nr_of_clients];
		////std::copy(client, client + (nr_of_clients - 1), temp);
		//memcpy(temp,client,nr_of_clients-1);
		//delete[] client;
		//client = temp;
		if (listener.accept(this->client[nr_of_clients - 1]) != sf::Socket::Done)
		{
			// error...
			std::cout << "error";
		}
		//this->receive(nr_of_clients-1);	
}

void ServerTCP::send(int which_client, std::string message)
{
	if (this->client[which_client].send(message.c_str(), message.length() + 1) != sf::Socket::Done)
	{
		std::cout << "Bl�d wysy�ania do klienta";
	}
}

void ServerTCP::receive(int which_client)
{
	char data[100];
	std::size_t received;
	std::string output_string;
	do
	{
		if (client[which_client].receive(&data, 100, received) != sf::Socket::Done)
		{
			// error...
			//std::cout << "Error during server receiveing";
		}
		std::string temp_string(data);
		output_string = temp_string;
		//std::cout << output_string << std::endl;
	} while (output_string.find("archive") == -1);

	std::cout << std::endl << "[SERVER] po odbiorze" << std::endl;

	//std::string	received_data_str(data);			//tworzymy nowy string na podstawie tablicy char�w
	tank[which_client].deserialize(output_string);							//tworzymy testowy obiekt czolg
	//czolg_test.deserialize(output_string);		//deserializujemy obiekt (czyli wczytujemy spowrotem wszystkie dane dla niego niezb�dne)
	
	std::cout << "[SERVER] Received " << received <<  " bytes" << " " << output_string << std::endl;
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
	


	for (int i = 0; i < clients_size; i++)
	{
		clients[i] = new sf::Thread(&ServerTCP::accept_client, this);
		clients[i]->launch();
		clients[i]->wait();
		std::cout << " Po��czono z klientem " << i << " [SERVER]" << std::endl;
		this->send(i, tank[i].serialize());	
		//this->send(i, std::to_string(i));
		
	}
	listener.close();
	while (1)
	{
		for (int i = 0; i < nr_of_clients - 1; i++)
		{
			std::cout << "Server petla " << i << std::endl;
			this->receive(i);
			std::cout << "Server petla " << i << std::endl;
			this->send(i, this->tank[i].serialize());
		}
	}
	
}
void ServerTCP::runGame()
{
	std::cout << "Server wszed� w tryb ci�g�y" << std::endl;
	while (1)
	{
		for (int i = 0; i < nr_of_clients - 1; i++)
		{
			
			this->receive(i);
			std::cout << "Server petla " << i << std::endl;
			this->send(i, this->tank[i].serialize());
		}
	}
		//this->send(0, std::to_string(nr_of_clients - 1));
	
}
