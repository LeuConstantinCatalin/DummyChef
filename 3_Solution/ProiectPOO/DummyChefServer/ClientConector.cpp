﻿#include "ClientConector.h"
#include "DbConector.h"
//#include"Admin.h"
ClientConector* ClientConector::instance = nullptr;
SOCKET ClientConector::listening;
bool ClientConector::con = true;
std::vector<IUser*> ClientConector::clienti;

ClientConector& ClientConector::createClientConector()
{
    if (!instance)
    {
        instance = new ClientConector;
    }

    return *instance;

}

void ClientConector::deleteClientConector()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void ClientConector::initializareWinSock()
{
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    int wsOK = WSAStartup(ver, &wsData);
    if (wsOK != 0) {
        std::cerr << "Nu s-a putut inițializa Winsock! Eroare: " << wsOK << std::endl;
        exit;
    }

}
void ClientConector::initializareSoketAscultare()
{
    // Creare socket
    listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        std::cerr << "Nu s-a putut crea socket-ul! Eroare: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }

    // Bind socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(12345);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;
    bind(listening, (sockaddr*)&hint, sizeof(hint));
    // Ascultă pentru conexiuni
    listen(listening, SOMAXCONN);
}
void ClientConector::manageUserType(SOCKET& clientSocket)
{
    std::string cerere=receive_message(clientSocket);
    size_t pos1 = cerere.find('|');
    size_t pos2 = cerere.find('|', pos1 + 1);
    size_t pos3 = cerere.find('|', pos2 + 1);

    // Extrage substringurile corespunzătoare fiecărei secțiuni
    std::string action = cerere.substr(0, pos1);
    std::string username = cerere.substr(pos1 + 1, pos2 - pos1 - 1);
    std::string password = cerere.substr(pos2 + 1, pos3 - pos2 - 1);
    std::string type = cerere.substr(pos3 + 1);

    if (action == "Login")
    {
        manageLoginAction(username, password, type, clientSocket);
    }
    else
        if (action == "SignUp")
        {
            manageSignUpAction(username, password, type, clientSocket);
        }
}
void ClientConector::manageLoginAction(std::string username,std::string password,std::string type, SOCKET& sock)
{
    //send_message(sock, "Login");

    //IUser* s = new Utilizator(sock);
    //clienti.push_back(std::move(s));
    std::string cautare = ("SELECT username, password, type FROM users WHERE username='" + username+"'");
    bool t=DbConector::efectueazaCautareUserInDb(cautare, username,password,type, sock);
    if (t == true)
    {
        ClientConector::send_message(sock, "Gasit");
        if (type == "utilizator")
        {
            IUser* s = new Utilizator(sock);
            ClientConector::addClientInVector(s);

            std::cout << "A acceptat utilizatorul " << username << "\n\n";
        }
        else
        {
            if (type == "bucatar")
            {
                IUser* s = new Bucatar(sock);
                ClientConector::addClientInVector(s);

                std::cout << "A acceptat bucatarul " << username << "\n\n";
            }
            else
            {
                if (type == "admin")
                {
                    IUser* s = new Admin(sock);
                    ClientConector::addClientInVector(s);

                    std::cout << "A acceptat adminul " << username << "\n\n";
                }
            }
        }
        
    }
    else
    { 
        ClientConector::send_message(sock, "Nu s-a gasit nicio potrivire.");
        closesocket(sock);
        sock = INVALID_SOCKET;
    }
}
void ClientConector::manageSignUpAction(std::string username, std::string password, std::string type, SOCKET sock)
{
    //send_message(sock, "SignUp");
    if (type == "utilizator")
    {
        std::string cautare = ("EXEC CheckUsernameExists " + username + ", users,resultMessage;");
        bool t1 = DbConector::cautaExistentaInTabel(sock, cautare);
        cautare = ("EXEC CheckUsernameExists " + username + ", bucatariRequest,resultMessage;");
        bool t2 = DbConector::cautaExistentaInTabel(sock, cautare);

        bool t=false;
        if (t1 == false && t2 == false)
        {
            std::string cautare = ("INSERT INTO users (username, password, type, activity) VALUES('" + username + "', '" + password + "', '" + type + "',1);");
            t = DbConector::insereazaUserInDb(cautare, sock);
        }
       
        if (t == true)
        {
            ClientConector::send_message(sock, "Inserat");
            IUser* s = new Utilizator(sock);
            ClientConector::addClientInVector(s);
        }
        else
        {
            ClientConector::send_message(sock, "Eroare la inserare");
            closesocket(sock);
            sock = INVALID_SOCKET;
        }
    }
    else
        if(type=="bucatar")
        {
        //std::string cautare = ("SELECT username FROM users WHERE username='" + username + "'");
            std::string cautare = ("EXEC CheckUsernameExists " +username+ ", users,resultMessage;");
            bool t1 = DbConector::cautaExistentaInTabel(sock, cautare);
            cautare = ("EXEC CheckUsernameExists " + username + ", bucatariRequest,resultMessage;");
            bool t2 = DbConector::cautaExistentaInTabel(sock, cautare);

            if (t1 == false&&t2==false )
            {
                cautare = ("INSERT INTO bucatariRequest (username, password) VALUES('" + username + "', '" + password + "');");
                bool t = DbConector::insereazaUserInDb(cautare, sock);
                if (t == true)
                {
                    ClientConector::send_message(sock, "Bucatar");
                }
                else
                {
                    ClientConector::send_message(sock, "Eroare la inserare");
                    closesocket(sock);
                    sock = INVALID_SOCKET;
                }
            }
            else
            {

                ClientConector::send_message(sock, "DEJA EXISTA");
                closesocket(sock);
                sock = INVALID_SOCKET;
            }
        }
}
void ClientConector::stopConnection(SOCKET client_socket)
{
    closesocket(client_socket);
    client_socket = INVALID_SOCKET;
}
bool ClientConector::isSocketConnected(SOCKET& socket)
{
    int error = 0;
    socklen_t len = sizeof(error);
    int retval = getsockopt(socket, SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&error), &len);
    if (retval != 0) {
        //std::cerr << "Eroare la getsockopt: " << strerror(errno) << std::endl;
        closesocket(socket);
        socket = INVALID_SOCKET;
        return false;
    }
    if (error != 0) {
        //std::cerr << "Eroare la conectarea la server: " << strerror(error) << std::endl;
        closesocket(socket);
        socket = INVALID_SOCKET;
        return false;
    }
    return true;
}
void ClientConector::initializareServer()
{
    initializareWinSock();
    initializareSoketAscultare();
    DbConector::createDbConector();
    DbConector::initializareConexiuneBd();
    std::thread acceptClientsThread(creereSoketNou);
    acceptClientsThread.detach();
}

void ClientConector::creereSoketNou()
{
    while (true) {
        sockaddr_in client;
        int clientSize = sizeof(client);
        SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Nu s-a putut accepta conexiunea! Eroare: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            clientSocket = INVALID_SOCKET;
            continue;
            //WSACleanup();
            exit;
        }
        else
        {
            manageUserType(clientSocket);
        }
    }
}

void ClientConector::send_message(const SOCKET client_socket, const char* cerere)
{
    send(client_socket, cerere, strlen(cerere), 0);
}

std::string ClientConector::receive_message( SOCKET client_socket)
{
    char buf[4096];

    // Primește cererea de la client
    ZeroMemory(buf, 4096);
    int bytesReceived = recv(client_socket, buf, 4096, 0);
    if (bytesReceived == SOCKET_ERROR) {
        std::cerr << "Eroare la primirea datelor de la client! Eroare: " << WSAGetLastError() << std::endl;
        closesocket(client_socket);
        client_socket= INVALID_SOCKET;
       // WSACleanup();
        exit;
    }

    if (bytesReceived <= 0) {
        // Închide conexiunea daca nu mai sunt date sau a avut loc o eroare
        //deconectare(current_sock);
        closesocket(client_socket);
        client_socket = INVALID_SOCKET;
        //FD_CLR(current_sock, &readfds); // Eliminam socket-ul din setul de descriptori monitorizati
        std::cout << "Client disconnected\n";
    }


    std::string cerere = std::string(buf, 0, bytesReceived);
    return cerere;
}
