#include "ClientConector.h"
#include "DbConector.h"
#include <thread> // Pentru std::thread
#include <vector>
#include"Utilizator.h"



int main() {
  
    ClientConector::createClientConector();
    ClientConector::initializareServer();


    while (true)
    {
        
    }

    return 0;
}
