#include "Admin.h"
#include "ClientConector.h"
#include"DbConector.h"
void Admin::play()
{
	std::cout << "Admin" << "\n\n";


	while (b == true)
	{
		if (ClientConector::isSocketConnected(socket) == true) {
			//ClientConector::receive_message(socket);
			//ClientConector::send_message(socket, "da");
			//std::cout << "Maine" << "\n\n";


			std::string s = ClientConector::receive_message(socket);

			std::cout << s << std::endl;
			if (s.substr(0, 11) == "addBucatari")
			{
				s.erase(0, 11);
				std::vector<int>v;
				v.push_back(1);
				DbConector::cautaViewRequesturi(socket, stoi(s), "username", "bucatariRequest",v);

			}
			else {
				std::cout << s.substr(0, 12);
				if (s.substr(0, 12) == "AddBucatarU|")
				{
					s.erase(0, 12);
					std::string procedura = "EXEC TransferBucatar @username =" + s + ";";
					bool g = DbConector::executaProceduraStocata(socket, procedura);
					if (g == true)
					{
						ClientConector::send_message(socket, "Adaugat");
					}
					else
						(ClientConector::send_message(socket, "NU S-A PUTUT MUTA"));

				}
				if (s.substr(0, 14) == "StergeBucatar|")
				{
					s.erase(0, 14);
					std::string procedura = "DELETE FROM bucatariRequest WHERE username = '" + s + "';";
					bool g = DbConector::executaProceduraStocata(socket, procedura);
					if (g == true)
					{
						ClientConector::send_message(socket, "Sters");
						std::chrono::nanoseconds interval(10000000);

						// Adãugarea întârzierii
						std::this_thread::sleep_for(interval);
					}
					else
						(ClientConector::send_message(socket, "EROARE LA STERGERE"));

				}
			}

			if (s.substr(0,9) == "editUsers")
			{
				s.erase(0, 9);
				std::vector<int>v;
				v.push_back(1);
				v.push_back(2);
				DbConector::cautaViewRequesturi(socket, stoi(s), "username, type", "users",v);

			}
			else {
				std::cout << s.substr(0, 11);
				if (s.substr(0, 11) == "changeType|")
				{
					s.erase(0, 11);
					std::string type = ClientConector::receive_message(socket);
					std::string procedura = "UPDATE users SET type = '"+type+ "' WHERE username = '" +s+ "'; ";
					bool g = DbConector::executaProceduraStocata(socket, procedura);
					if (g == true)
					{
						ClientConector::send_message(socket, "Modificat");
					}
					else
						(ClientConector::send_message(socket, "NU S-A PUTUT MODIFICA"));

				}
				if (s.substr(0, 11) == "stergeUser|")
				{
					s.erase(0, 11);
					std::string procedura = "DELETE FROM users WHERE username = '" + s + "';";
					bool g = DbConector::executaProceduraStocata(socket, procedura);
					if (g == true)
					{
						ClientConector::send_message(socket, "Sters");
					}
					else
						(ClientConector::send_message(socket, "EROARE LA STERGERE"));

				}
			}
			

		}
		/*else
		{
			b = false;
			std::cout << "Am terminat cu adminul\n";
		}*/


		//std::cout << "da\n";

		//std::cout << "Poimaine" << "\n\n";

	}
	//myth.join();
}

