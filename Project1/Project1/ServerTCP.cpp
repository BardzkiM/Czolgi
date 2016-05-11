#include "ServerTCP.h"
#include "Czolg.h"
ServerTCP::ServerTCP()
{

}

ServerTCP::~ServerTCP()
{

}

void ServerTCP::accept_client()
{
	std::cout << "Oczekiwanie na akceptacjê klienta"<< std::endl;
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
	client[which_client].send(message.c_str(),message.length()+1);
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
	std::string	received_data_str(data);			//tworzymy nowy string na podstawie tablicy charów
	Czolg czolg_test;								//tworzymy testowy obiekt czolg
	czolg_test.deserialize(received_data_str);		//deserializujemy obiekt (czyli wczytujemy spowrotem wszystkie dane dla niego niezbêdne)
	
	std::cout << "Received " << received <<  " bytes" << " " << received_data_str << std::endl;
}

void ServerTCP::Run()
{
	std::cout << std::endl << "Start w¹tku servera "<< argument << std::endl;
	//sf::TcpListener listener; // tworzymy gniazdo nas³uchujace
	unsigned int port = 54000; // port, na którym bêdziemy nas³uchiwaæ

	if (listener.listen(port) != sf::Socket::Done) // rozpoczynamy nas³uchiwanie na porcie 'port'
	{
		std::cerr << "Nie mogê rozpocz¹æ nas³uchiwania na porcie " << port << std::endl;
		exit(1);
	}
	
	sf::Thread client_1(&ServerTCP::accept_client, this);
	sf::Thread client_2(&ServerTCP::accept_client, this);
	sf::Thread client_3(&ServerTCP::accept_client, this);
	sf::Thread client_4(&ServerTCP::accept_client, this);

	client_1.launch();
	client_1.wait();
	std::cout << "Poczeka³ na zakoñczenie w¹tku 1"<<std::endl;
	this->receive(0);
	this->send(0, "Wiadomosc poszla");

	client_2.launch();
	client_2.wait();
	std::cout << "Poczeka³ na zakoñczenie w¹tku 2" << std::endl;
	this->receive(1);

	client_3.launch();
	client_3.wait();
	std::cout << "Poczeka³ na zakoñczenie w¹tku 3" << std::endl;
	this->receive(2);

	client_4.launch();
	client_4.wait();
	std::cout << "Poczeka³ na zakoñczenie w¹tku 4" << std::endl;
	this->receive(3);
	
	

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

