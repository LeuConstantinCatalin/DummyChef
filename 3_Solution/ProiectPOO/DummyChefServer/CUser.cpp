#include "CUser.h"


#include"ClientConector.h"
CUser::CUser(SOCKET sock)
{
	socket = sock;
	t = true;
	//startThread();
	
}

void CUser::play()
{
	{ std::cout << 1 << "\n\n";

	while (t == true)
	{
		if (ClientConector::isSocketConnected(socket) == true) {
			ClientConector::receive_message(socket);
			ClientConector::send_message(socket, "da");
			std::cout << "Maine" << "\n\n";
		}
		else
		{
			t = false;
		}

	}
	}
}

