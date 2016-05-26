#include "ServerTCP.h"
#include "Czolg.h"
#include "GraDane.h"
#include <chrono>

using namespace std::chrono;



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

std::string ServerTCP::serialize()
{
	std::ostringstream archive_ostream;
	std::string serialized_data_str;
	boost::archive::text_oarchive oarchive(archive_ostream);
	oarchive << this->nr_of_clients;
	serialized_data_str = archive_ostream.str();
	//std::cout << "[Server]serialized data: " << serialized_data_str << std::endl;
	return serialized_data_str;

}

void ServerTCP::accept_client()
{
	std::cout << "Oczekiwanie na akceptacjê klienta"<< std::endl;
		
		//sf::TcpSocket *temp = new sf::TcpSocket[nr_of_clients];
		////std::copy(client, client + (nr_of_clients - 1), temp);
		//memcpy(temp,client,nr_of_clients-1);
		//delete[] client;
		//client = temp;
		if (listener.accept(this->client[nr_of_clients]) != sf::Socket::Done)
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
		std::cout << "Bl¹d wysy³ania do klienta";
	}
}

void ServerTCP::receive(int which_client)
{
	char data[1500];
	std::size_t received;
	std::string output_string;
	do
	{
		if (client[which_client].receive(&data, 1500, received) != sf::Socket::Done)
		{
			// error...
			//std::cout << "Error during server receiveing";
		}
		std::string temp_string(data);
		output_string = temp_string;
		//std::cout << output_string << std::endl;
	} while (output_string.find("archive") == -1);

	//std::cout << std::endl << "[SERVER] po odbiorze" << std::endl;

	//std::string	received_data_str(data);			//tworzymy nowy string na podstawie tablicy charów
	tank[which_client].deserializeForServer(output_string);							//tworzymy testowy obiekt czolg
	//czolg_test.deserialize(output_string);		//deserializujemy obiekt (czyli wczytujemy spowrotem wszystkie dane dla niego niezbêdne)
	
	//std::cout << "[SERVER] Received " << received <<  " bytes" << " " << output_string << std::endl;
}

void ServerTCP::RunInit()
{
	std::cout << std::endl << "Start w¹tku servera "<< argument << std::endl;
	//sf::TcpListener listener; // tworzymy gniazdo nas³uchujace
	unsigned int port = 54000; // port, na którym bêdziemy nas³uchiwaæ

	if (listener.listen(port) != sf::Socket::Done) // rozpoczynamy nas³uchiwanie na porcie 'port'
	{
		std::cerr << "Nie mogê rozpocz¹æ nas³uchiwania na porcie " << port << std::endl;
		exit(1);
	}
	const int max_clients_size = 4;
	sf::Thread *clients[max_clients_size];
	


	for (int i = 0; i < max_clients_size; i++)
	{
		clients[i] = new sf::Thread(&ServerTCP::accept_client, this);
		clients[i]->launch();
		clients[i]->wait();
		//std::cout << " Po³¹czono z klientem " << i << " [SERVER]" << std::endl;
		tank[i].nr_czolgu = i;
		this->send(i, tank[i].serialize());	// wysy³amy do klienta jest pocz¹tkowe po³o¿enie 
		//this->send(i, std::to_string(i));
		nr_of_clients++;
		
	}
	listener.close();
	/*while (1)
	{
		for (int i = 0; i < nr_of_clients - 1; i++)
		{
			std::cout << "Server petla " << i << std::endl;
			this->receive(i);

			std::cout << "Server petla " << i << std::endl;

			
			this->send(i, this->tank[i].serialize());
		}
	}*/
	
}
void ServerTCP::runGame()
{
	const int nr_of_clients_const = nr_of_clients;
	std::cout << "Server wszed³ w tryb ci¹g³y" << std::endl;
	
	for (int i = 0; i < nr_of_clients_const; i++) // wysy³amy iloœæ klientów do wszystkich klientów
	{
		this->send(i, this->serialize());
	}
	sf::Clock clock;
	while (1)
	{
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		//std::cout << "###################[Server] numer klientów " << nr_of_clients_const << std::endl;
		for (int i = 0; i < nr_of_clients_const; i++)
		{
			
			this->receive(i);
			sprawdzCzyStrzelil(i);

			movePociski(i, clock);
			
			for (int j = 0; j < nr_of_clients_const; j++)
			{				
				this->send(i, this->tank[j].serialize());
				std::cout << "[ServerTCP] wys³ano" << this->tank[j].serialize() <<std::endl;
			}
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(t2 - t1).count();
		std::cout << "[ServerTCP] runGame " << nr_of_clients_const << " "<< duration << std::endl;
	}
		//this->send(0, std::to_string(nr_of_clients_const - 1));
	
}

void ServerTCP::movePociski(int index, sf::Clock &clock)
{
	if (clock.getElapsedTime().asMilliseconds() > 10)
	{
		tank[index].sprawdzKolizjePociskowPrzeszkod();
		sprawdzKolizjePociskCzolg(index);
		clock.restart();
	}
}
void ServerTCP::sprawdzCzyStrzelil(int index)
{
	if (tank[index].strzelilem)
	{
		tank[index].strzelilem = false;
		tank[index].addPocisk();
	}
}
void ServerTCP::sprawdzKolizjePociskCzolg(int index)
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (int k = 0; k < tank[index].pociski.size(); k++)
	{
		Pocisk *pocisk = &tank[index].pociski[k];


		for (int i = 0; i < nr_of_clients; i++)
		{

			if (((pocisk->x + pocisk->width) > tank[i].x) &&
				(pocisk->x < (tank[i].x + tank[i].width)) &&
				((pocisk->y + pocisk->height) >  tank[i].y) &&
				(pocisk->y < (tank[i].y + tank[i].height )))
			{
				tank[index].removePocisk(k);
				tank[i].hp -= 25;
			}
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	//std::cout << "[ServerTCP] sprawdzKolizjePociskCzolg " << duration << std::endl;
}