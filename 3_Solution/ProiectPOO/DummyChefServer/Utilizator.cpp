#include "Utilizator.h"

#include"ClientConector.h"
void Utilizator::play()
{

	std::cout << "Utilizator" << "\n\n";
	//while (true)
	//{
	//	ClientConector::receive_message(socket);
	//	ClientConector::send_message(socket,"da");
	//}

	while (t==true)
	{
		if (ClientConector::isSocketConnected(socket) == true) {
			ClientConector::receive_message(socket);
			ClientConector::send_message(socket, "da");
			std::cout << "Poimaine" << "\n\n";
		}
		else
		{
			t=false;
		}
		
	}
}
