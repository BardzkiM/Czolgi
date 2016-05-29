#include "ClientTCP.h"
#include "Czolg.h"

using boost::asio::ip::tcp;

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
	//if (socket.send(message.c_str(), message.length() + 1) != sf::Socket::Done)
	//{
	//	// error...
	//	std::cout << "error";
	//}
	char request[1024];
	/*std::cin.getline(request, 1024);
	size_t request_length = std::strlen(message);*/
	boost::asio::write(*socket, boost::asio::buffer(message.c_str(), message.length()));
}

std::string ClientTCP::receive()
{
	//char data[200];
	//std::size_t received;
	//std::string output_string;
	//do
	//{
	//	if (socket.receive(&data, 200, received) != sf::Socket::Done)
	//	{
	//		// error...
	//		std::cout << "Error during client receiveing";
	//	}
	//	std::string temp_string(data);
	//	output_string = temp_string;
	//	//std::cout <<"[ClientTCP] receive"<< output_string << std::endl;
	//} while (output_string.find("archive")==-1);

	char reply[1024];
	std::string output_string;
	size_t reply_length = boost::asio::read(*socket, boost::asio::buffer(reply, 1024));
	std::cout << "Reply is: ";
	std::cout.write(reply, reply_length);
	std::cout << "\n";
	std::string temp_string(reply);
	output_string = temp_string;
	
	//std::cout << "Odebrano: " << output_string << std::endl;
	return output_string;
}

void ClientTCP::RunInit()
{
	sf::Time delay_complete_transmission = sf::seconds(0.005);
	std::cout << "Start w¹tku klienta" << std::endl;

	//sf::Socket::Status status = socket.connect(this->adress, 54000);
	//if (status != sf::Socket::Done)
	//{
	//	// error...
	//	std::cout << "error";
	//}
	socket = new tcp::socket(io_service);
	tcp::resolver resolver(io_service);
	boost::asio::connect(*socket, resolver.resolve({ "127.0.0.1", "54000" }));
	
	
	this->tank->deserialize(this->receive()); // odbieramy w³asny czo³g przed gr¹

	deserialize(this->receive());	//odbieramy liczbê klientów
	std::cout <<std::endl<< "Klient wszed³ w tryb ci¹g³y" << std::endl;
	while (1)
	{
		//std::cout << "jestem w ³ajlu Klienta  !!!!!!!!!" << nr_of_clients << std::endl;
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
