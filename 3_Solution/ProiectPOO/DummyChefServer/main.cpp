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
        //auto it = ClientConector::clienti.begin();
        // 
        for(int i =0;i< ClientConector::clienti.size();i++)
            if (ClientConector::clienti[i]->getSocket() == INVALID_SOCKET)
            {

                IUser* aux = std::move(ClientConector::clienti[i]);
                delete aux;
                //delete ClientConector::clienti[2];

                // Ștergem al treilea element din vector
                ClientConector::clienti.erase(ClientConector::clienti.begin() + i);
                i--;
            }
        //while (it != ClientConector::clienti.end()) {
        //    if ((*it)->getSocket() == INVALID_SOCKET) {
        //        delete* it; // Eliberează memoria
        //        it = ClientConector::clienti.erase(it);
        //    }
        //    else {
        //        ++it;
        //    }
        //}
    }

    return 0;
}
