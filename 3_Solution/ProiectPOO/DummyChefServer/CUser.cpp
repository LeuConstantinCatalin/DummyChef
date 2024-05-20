#include "CUser.h"


#include"ClientConector.h"
CUser::CUser(SOCKET sock)
{
	socket = sock;
	b = true;
	//startThread();
	
}

void CUser::play()
{
	std::cout << "CUSER\n";


	while (b == true)
	{
		if (ClientConector::isSocketConnected(socket) == true) {
			

			std::string s = ClientConector::receive_message(socket);
			
		}
		else
		{
			b = false;
			std::cout << "Am terminat cu cuserul\n";
		}


		

	}
	//myth.join();
	
}

