#include <iostream>
#include<string>
#include <WS2tcpip.h>
#include <tchar.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <codecvt>

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "odbc32.lib")


int main() {

    //server
    // Inițializare Winsock
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    int wsOK = WSAStartup(ver, &wsData);
    if (wsOK != 0) {
        std::cerr << "Nu s-a putut inițializa Winsock! Eroare: " << wsOK << std::endl;
        return -1;
    }


    //db
    // Conectare la baza de date
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLRETURN retcode;
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    // Definirea șirului de conexiune folosind TEXT()
    TCHAR connString[] = TEXT("DRIVER={SQL Server};SERVER=DESKTOP-K4RIHE6;DATABASE=TEST_DB;UID=;PWD=;");
    retcode = SQLDriverConnect(hdbc, NULL, connString, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);

    // Verificare eroare la conectare
    if (!SQL_SUCCEEDED(retcode)) {
        std::cerr << "Eroare la conectarea la baza de date!" << std::endl;
        return -1;
    }

    // Creare socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        std::cerr << "Nu s-a putut crea socket-ul! Eroare: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }

    // Bind socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;
    bind(listening, (sockaddr*)&hint, sizeof(hint));

    // Ascultă pentru conexiuni
    listen(listening, SOMAXCONN);

    while (true) {
        // Așteaptă conexiuni
        sockaddr_in client;
        int clientSize = sizeof(client);
        SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
        
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Nu s-a putut accepta conexiunea! Eroare: " << WSAGetLastError() << std::endl;
            closesocket(listening);
            WSACleanup();
            return -1;
        }

        //// Inchide socket-ul de ascultare
        //closesocket(listening);

        char buf[4096];

        // Primește cererea de la client
        ZeroMemory(buf, 4096);
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Eroare la primirea datelor de la client! Eroare: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            WSACleanup();
            return -1;
        }

        std::string cerere = std::string(buf, 0, bytesReceived);

        // Parsează cererea și răspunde
        if (cerere.find("CautaNume|") != std::string::npos) {
            std::string numeDeCautat = cerere.substr(10); // Eliminați "CautaNume|"
            
            SQLHSTMT hstmt;
            retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
          
            // Definește interogarea SQL utilizând un șir wide

            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring wide_query = converter.from_bytes("SELECT * FROM users WHERE username='" + numeDeCautat + "'");

            // Execută interogarea SQL
            SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);

            SQLCHAR col1[255];
            SQLLEN cbCol1;
            BOOL t = false;
            while (SQLFetch(hstmt) == SQL_SUCCESS) {
                SQLGetData(hstmt, 2, SQL_C_CHAR, col1, sizeof(col1), &cbCol1);
                // Trimiteți rezultatul înapoi la client
                send(clientSocket, (const char*)col1, cbCol1, 0);
                t = true;
            }
            if(t==false)
                send(clientSocket, "Nu s-a gasit nicio potrivire.", 29, 0);
            SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        }
        if (cerere.find("InsereazaDate|") != std::string::npos) {
            std::string dateDeInserat = cerere.substr(14); // Eliminați "InsereazaDate|"

            SQLHSTMT hstmt;
            retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            // Construiți instrucțiunea SQL pentru inserare
            std::wstring wide_insert_query = converter.from_bytes("INSERT INTO users (username, is_active) VALUES ('" + dateDeInserat + "', 1)");

            // Execută instrucțiunea SQL de inserare
            retcode = SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_insert_query.c_str())), SQL_NTS);

            // Trimitere răspuns către client (opțional)
            if (SQL_SUCCEEDED(retcode)) {
                send(clientSocket, "Datele au fost inserate cu succes.", 34, 0);
            }
            else {
                send(clientSocket, "Eroare la inserarea datelor.", 29, 0);
            }
        }
       // send(clientSocket, "", 1, 0);
         // Deconectare
        closesocket(clientSocket);
    }

    // Închideți socket-ul de ascultare
    closesocket(listening);

    // Cleanup Winsock
    WSACleanup();

    return 0;
}