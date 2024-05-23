#include "Utilizator.h"
#include"DbConector.h"
#include"ClientConector.h"
#include <sstream>
#include <string>
#include <vector>
#include <utility>


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

		}
		else
		{
			b = false;
			std::cout << "Am terminat cu utilizatorul\n";
		}

	}
	//myth.join();
}
