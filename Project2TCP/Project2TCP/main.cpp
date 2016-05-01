#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	sf::TcpSocket socket;
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	char connectionType, mode;
	string text;
	char buffer[2000];
	size_t recieved;
	string a;

	cout << "s serv, c cli" << endl;
	cin >> connectionType;
	while(true)
	{
	if (connectionType == 's')
	{
		sf::TcpListener listener; // ustawiamy listnera dla servera
		listener.listen(2000);
		listener.accept(socket);
		text = "wiadomosc od servera";
		cin >> a;
		socket.send(text.c_str(), text.length() + 1);
		socket.send(a.c_str(), a.length() + 1);


	}
	else if (connectionType == 'c')
	{
		socket.connect(ip, 2000);
		text = "wiadomosc od klienta";
		cin >> a;
		socket.send(text.c_str(), text.length() + 1);
		socket.send(a.c_str(), a.length() + 1);
	}

	socket.receive(buffer, sizeof(buffer), recieved);

	cout << buffer << endl;

	socket.receive(buffer, sizeof(buffer), recieved);

	cout << buffer << endl;
}
	system("pause");
	return 0;

}
/*
sf::Packet packet:
packet << tank.x << tank.y;
socket.send(packet);socket.recive(packet);
if(packet >> tank2.x >> tank2.y)
tank2.setposistion

*/