/*JESZCZE NIE DZIALA POPRAWNIE
PODCZAS KOMPILACJI CALEGO PROJEKTU - TEN PLIK ZAKOMENTOWAC!*

#include "SFML\Network.hpp"
#include <string>
#include<iostream>
#include <cstdio>
using namespace std;
using namespace sf;
int main()
{
	IpAddress ip = IpAddress::getLocalAddress();
	TcpSocket socket;
	char connectionType;

	char mode;//rola serwera lub rola klienta
	string message = "";
	char buffer[2000];
	size_t received;//ilosc bajtow, ktore sa przesylane



	cout << "Enter s for server or enter c for client" << endl;
	cin >> connectionType;
	if (connectionType == 's') //server
	{
		TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);

		message += "Tu SERWER, placzenie zostalo nawiazane \n";
		mode = 's'; //send - tryb wysylania

	}
	else if (connectionType == 'c') //client
	{
		socket.connect(ip, 2000); //adres ip, port przez który siê ³¹cz¹
		message += "Tu KLIENT, polaczenie zostalo nawiazane \n";
		mode = 'r'; //received - tryb otrzymywania
	}

	socket.send(message.c_str(), message.length() + 1);

	socket.receive(buffer, sizeof(buffer), received);
	cout << buffer << endl;

	bool done = true;
	while (done)
	{
		if (mode == 's')
		{
			getline(cin, message);
			socket.send(message.c_str(), message.length() + 1);
			message = 'r';
		}
		else if (mode == 'r')
		{
			socket.receive(buffer, sizeof(buffer), received);
			//if (received > 0)
			//{
			cout << "received: " << buffer << endl;
			mode = 's';
			//	}
		}
	}

	return 0;

	system("pause");//by nie zamykal sie za szybko


*/