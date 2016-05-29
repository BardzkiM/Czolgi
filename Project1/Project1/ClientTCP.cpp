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
	boost::asio::write(socket, boost::asio::buffer(message.c_str(), message.length()));
}

std::string ClientTCP::receive(boost::asio::ip::tcp::socket socket)
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
	try {
		char reply[1024];
		std::string output_string;
		size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply, 1024));
		std::cout << "Reply is: ";
		std::cout.write(reply, reply_length);
		std::cout << "\n";
		std::string temp_string(reply);
		output_string = temp_string;
		return output_string;
	}
	catch (const std::exception& error) {
		// Should print the actual error message
		std::cerr<< "[ClientTCP] " << error.what() << std::endl;
	}
	
	
	//std::cout << "Odebrano: " << output_string << std::endl;
	
}

void ClientTCP::RunInit()
{
	sf::Time delay_complete_transmission = sf::seconds(0.005);
	std::cout << "Start w¹tku klienta" << std::endl;
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service);
	boost::asio::ip::tcp::resolver resolver(io_service);
	//sf::Socket::Status status = socket.connect(this->adress, 54000);
	//if (status != sf::Socket::Done)
	//{
	//	// error...
	//	std::cout << "error";
	//}
	/*socket = new tcp::socket(io_service);
	resolver = new tcp::resolver(io_service);*/
	try {
			boost::asio::connect(socket, resolver.resolve({ "127.0.0.1", "54000" }));


			this->tank->deserialize(this->receive(socket)); // odbieramy w³asny czo³g przed gr¹
		}
		catch (const std::exception& error) {
			// Should print the actual error message
			std::cerr << error.what() << std::endl;
		}
	
	

	deserialize(this->receive(socket));	//odbieramy liczbê klientów
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
			tanks[i].deserialize(this->receive(socket));
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
