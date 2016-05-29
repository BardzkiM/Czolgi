#include "ServerTCP.h"
#include "Czolg.h"
#include "GraDane.h"
#include <chrono>

using namespace std::chrono;
using boost::asio::ip::tcp;


ServerTCP::ServerTCP()
{
	tank[0].setInitialPosition(0, 0);
	tank[1].setInitialPosition(1140, 840);
	tank[2].setInitialPosition(0, 840);
	tank[3].setInitialPosition(1140, 0);

	if (!buffer.loadFromFile("sounds/bomb.wav"))
	{
		std::cerr << "blad czytania dzwieku niszczenia (bomb.wav)!" << std::endl;
		exit(-12);
	}
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
	//std::cout << "Oczekiwanie na akceptacjê klienta"<< std::endl;
	//	

	//	if (listener.accept(this->client[nr_of_clients]) != sf::Socket::Done)
	//	{
	//		// error...
	//		std::cout << "error";
	//	}
	
	tcp::socket sock(io_service);
	a->accept(sock);
	client[nr_of_clients] = &sock;	
	
}

void ServerTCP::send(int which_client, std::string message)
{
	/*if (this->client[which_client].send(message.c_str(), message.length() + 1) != sf::Socket::Done)
	{
		std::cout << "Bl¹d wysy³ania do klienta";
	}*/
	boost::asio::write(*client[which_client], boost::asio::buffer(message.c_str(), message.length()));
}

void ServerTCP::receive(int which_client)
{
	/*char data[200];
	std::size_t received;
	std::string output_string;*/
	/*do
	{
		if (this->client[which_client].receive(&data, 200, received) != sf::Socket::Done)
		{
			std::cout << "Error during server receiveing";
		}
		std::string temp_string(data);
		output_string = temp_string;
	} while (output_string.find("archive") == -1);*/
	char data[1024];
	std::string output_string;
	boost::system::error_code error;
	size_t length = client[which_client]->read_some(boost::asio::buffer(data), error);
	if (error == boost::asio::error::eof)
		std::cout << "Connection closed cleanly by peer.";//break; // Connection closed cleanly by peer.
	else if (error)
	{
		std::cout << "[ServerTCP] receive error" << std::endl;
		throw boost::system::system_error(error); // Some other error.
	}
		
	std::string temp_string(data);
	output_string = temp_string;
	tank[which_client].deserializeForServer(output_string);							//tworzymy testowy obiekt czolg
}

void ServerTCP::RunInit()
{
	std::cout << std::endl << "Start w¹tku servera "<< argument << std::endl;
	unsigned int port = 54000; // port, na którym bêdziemy nas³uchiwaæ
	a = new tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), 54000));
	//if (listener.listen(port) != sf::Socket::Done) // rozpoczynamy nas³uchiwanie na porcie 'port'
	//{
	//	std::cerr << "Nie mogê rozpocz¹æ nas³uchiwania na porcie " << port << std::endl;
	//	exit(1);
	//}
	const int max_clients_size = 4;
	sf::Thread *clients[max_clients_size];
	


	for (int i = 0; i < max_clients_size; i++)
	{ 
		clients[i] = new sf::Thread(&ServerTCP::accept_client, this);
		clients[i]->launch();
		clients[i]->wait();
		tank[i].nr_czolgu = i;
		this->send(i, tank[i].serialize());	// wysy³amy do klienta jest pocz¹tkowe po³o¿enie 
		nr_of_clients++;
		
	}
	/*listener.close();*/
	
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
	sf::Time latency = sf::seconds(0.021);
	while (1)
	{
		for (int i = 0; i < nr_of_clients_const; i++)
		{
			sf::sleep(latency);
			this->receive(i);
			sprawdzCzyStrzelil(i);
			movePociski(i, clock);
			
			for (int j = 0; j < nr_of_clients_const; j++)
			{				
				this->send(i, this->tank[j].serialize());
			}
		}
	}
	
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
	sound.setBuffer(buffer);
	
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
				sound.play();
			}
		}
	}
}