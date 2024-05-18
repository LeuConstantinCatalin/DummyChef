#include "ClientConector.h"
#include "DbConector.h"
#include <thread> // Pentru std::thread
#include <vector>
#include"Utilizator.h"



int main() {
  
    ClientConector::createClientConector();
    ClientConector::initializareServer();
    std::string result;
    DbConector::executeQuery("SELECT * FROM retete", result);
    std::cout << std::endl << result << std::endl;
    while (true)
    {
        
    }

    return 0;
}
