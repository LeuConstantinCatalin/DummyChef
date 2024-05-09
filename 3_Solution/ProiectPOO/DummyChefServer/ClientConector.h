#pragma once
#include<iostream>
#include<string>
#include <WS2tcpip.h>
#include<vector>
#include<thread>

//#include <sys/socket.h>
#include <cerrno>

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "odbc32.lib")

//#include"ISign.h";

#include"Utilizator.h"
class ClientConector
{
private:
    static ClientConector* instance;
    static SOCKET listening;
    
    ClientConector(){};
    ~ClientConector() {};

    static void initializareWinSock();
    
    static void initializareSoketAscultare();
    static void manageUserType(SOCKET &socket);
    static void manageLoginAction(std::string username, std::string password, std::string type, SOCKET& sock);
    static void manageSignUpAction(std::string username, std::string password, std::string type, SOCKET sock);
   
public:
    static std::vector<IUser*> clienti;
    static ClientConector& createClientConector();
    static void deleteClientConector();
    
    static void initializareServer();
    static void creereSoketNou();
   
   static void send_message(const SOCKET client_socket,const char* cerere);
   static std::string receive_message(const SOCKET client_socket);
   static bool isSocketConnected(SOCKET& socket);
   static void addClientInVector(IUser*& s) { clienti.push_back(std::move(s)); clienti.back()->startThread();
   std::cout << "Am logat clientul un nou user ";
   }
    //static void disconnectFromClient();
};

