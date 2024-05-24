#include "Admin.h"
#include "ClientConector.h"
#include"DbConector.h"
#include <sstream>
#include <string>
#include <vector>
#include <utility>


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
			if (s == "ToateIngredientele")
			{
				std::string result;
				DbConector::RequestToateIngredientele("EXEC RequestToateIngredientele", result);
				ClientConector::send_message(socket, result.c_str());
			}

			if (s == "ToateRetetele")
			{
				std::string result;
				DbConector::RequestToateRetetele(result);
				ClientConector::send_message(socket, result.c_str());
			}

			if (s == "Activity")
			{
				std::string result;
				result.append("Top Utilizatori:\n");
				DbConector::RequestActivity("EXEC ActivityUtilizator", result);
				result.append("\nTop Bucatari:\n");
				DbConector::RequestActivity("EXEC ActivityBucatar", result);
				ClientConector::send_message(socket, result.c_str());
				std::cout << "\n\n" << result << "\n\n";
			}

			if (s == "Cumparaturi")
			{
				double pret = 0;
				s.clear();
				std::string s = ClientConector::receive_message(socket);

				std::vector<std::pair<std::string, int>> pairs;

				std::stringstream ss(s);
				std::string line;

				while (std::getline(ss, line)) {
					std::istringstream lineStream(line);
					std::string name;
					int number;
					lineStream >> name >> number;
					pairs.push_back(std::make_pair(name, number));
				}

				std::string response;
				for (const auto& pair : pairs) {
					std::cout << "Name: " << pair.first << ", Number: " << pair.second << std::endl;

					std::string query = "EXEC Cumparaturi " + pair.first;

					DbConector::RequestCumparaturi(query, response, pair.second, pret);
					std::cout << "\n\n" << response << "\n\n";
				}
				std::string str = std::to_string(pret);
				response.append("Pret total: ");
				response.append(str);
				response.append("\n");
				ClientConector::send_message(socket, response.c_str());
			}



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

