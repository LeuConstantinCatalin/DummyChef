#include "Utilizator.h"

#include"ClientConector.h"

void Utilizator::play()
{

	std::cout << "Utilizator" << "\n\n";
	

	/*while (ClientConector::isSocketConnected(socket) == true)
	{
			ClientConector::receive_message(socket);
			ClientConector::send_message(socket, "da");
			std::cout << "Poimaine" << "\n\n";
	}
	b = false;*/


	while (b == true)
	{
		if (ClientConector::isSocketConnected(socket) == true) {
			

			std::string s = ClientConector::receive_message(socket);
			
		}
		else
		{
			b = false;
			std::cout << "Am terminat cu utilizatorul\n";
		}

	}
	//myth.join();
}
