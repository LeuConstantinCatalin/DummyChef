#include "DbConector.h"
#include "ClientConector.h"

#include <thread>
#include <chrono>

SQLHDBC DbConector::hdbc;
DbConector* DbConector::instance = nullptr;

void DbConector::initializareConexiuneBd()
{
    // Conectare la baza de date
    SQLHENV henv;
   // SQLHDBC hdbc;
    SQLRETURN retcode;
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    // Definirea șirului de conexiune folosind TEXT()
    TCHAR connString[] = TEXT("DRIVER={SQL Server};SERVER=ASUSVIVOBOOKLEU\\MSSQLSERVER01;DATABASE=DummyChef;UID=;PWD=;");
    retcode = SQLDriverConnect(hdbc, NULL, connString, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);

    // Verificare eroare la conectare
    if (!SQL_SUCCEEDED(retcode)) {
        std::cerr << "Eroare la conectarea la baza de date!" << std::endl;
        return;
    }
    else
        std::cout << "conectat la baza de date";
}
DbConector& DbConector::createDbConector()
{
	if (instance == nullptr)
	{
		instance = new DbConector;
	}
	return *instance;
}

void DbConector::deleteDbConector()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

bool DbConector::efectueazaCautareUserInDb(const std::string& cautare, const std::string& usern, const std::string& parola, const std::string& userType,SOCKET& socket)
{
    SQLHSTMT hstmt;
    SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    // Definește interogarea SQL utilizând un șir wide

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_query = converter.from_bytes(cautare);

    // Execută interogarea SQL
    SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);

    SQLCHAR username[255];
    SQLCHAR password[255];
    SQLCHAR usertype[255];
    SQLLEN cbUsername, cbPassword, cbUsertype;

    BOOL adv = false;
  
     if (SQLFetch(hstmt) == SQL_SUCCESS) {
        SQLGetData(hstmt, 1, SQL_C_CHAR, username, sizeof(username), &cbUsername);
        SQLGetData(hstmt, 2, SQL_C_CHAR, password, sizeof(password), &cbPassword);
        SQLGetData(hstmt, 3, SQL_C_CHAR, usertype, sizeof(usertype), &cbUsertype);

        // Trimit rezultatul înapoi la client
        std::string user = std::string(reinterpret_cast<char*>(username), cbUsername);
        std::string pass = std::string(reinterpret_cast<char*>(password), cbPassword);
        std::string ut = std::string(reinterpret_cast<char*>(usertype), cbUsertype);

        if (user == usern && pass == parola && ut == userType)
        {
            return true;
        }
     }

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return false;
}

bool DbConector::insereazaUserInDb(const std::string& cautare, SOCKET& socket)
{
    bool g = DbConector::executaProceduraStocata(socket, cautare);
    return g;

}

void DbConector::cautaViewRequesturi(const SOCKET& socket, int nrAnterior, const std::string whatISelect, const std::string table, std::vector<int>v)
{
  
   
    SQLHANDLE hStmt;
    SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hStmt);

    ret = SQLFreeStmt(hStmt, SQL_CLOSE); // Eliberăm statementul anterior

    // Re-alocăm handle-ul pentru a executa o nouă interogare
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hStmt);

    int numarUtilizatori = 0;
    //int nrAnterior = std::stoi(ClientConector::receive_message(socket));
    int x=0;
    //nrAnterior += 10;
    // Executare interogare

    std::string cautare;
 
        //cautare = "SELECT username FROM users WHERE id > " + std::to_string(nrAnterior) + " AND id <= " + std::to_string(nrAnterior + 10);
    std::string g= "users";
    cautare = "SELECT COUNT(*) FROM "+table ;
    //cautare = "SELECT username FROM users WHERE id > " + std::to_string(0) + " AND id <= " + std::to_string(10);
   
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_query = converter.from_bytes(cautare);

    // Execută interogarea SQL
    ret = SQLExecDirect(hStmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);

    

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        // Citire rezultat

       // std::string var;
        SQLINTEGER numar;
        ret = SQLFetch(hStmt);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            ret = SQLGetData(hStmt, 1, SQL_C_LONG, &numar, 0, NULL);
            if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
                numarUtilizatori = static_cast<int>(numar);
                std::cout << "Numarul total de utilizatori: " << numarUtilizatori << std::endl;
                int aux=numarUtilizatori - nrAnterior;
                    
                if (aux >= 0)
                {
                    
                    if (aux >= 10)
                    {
                        ClientConector::send_message(socket, std::to_string(10).c_str());
                        std::chrono::nanoseconds interval(10000000);

                        // Adăugarea întârzierii
                        std::this_thread::sleep_for(interval);
                       ClientConector::send_message(socket, std::to_string(numarUtilizatori).c_str());
                        
                        x = 1;

                       // std::chrono::nanoseconds interval(10000000);

                        // Adăugarea întârzierii
                        std::this_thread::sleep_for(interval);
                    }
                    else
                    {
                        ClientConector::send_message(socket, std::to_string(aux).c_str());
                        std::chrono::nanoseconds interval(10000000);

                        // Adăugarea întârzierii
                        std::this_thread::sleep_for(interval);
                        ClientConector::send_message(socket, std::to_string(numarUtilizatori).c_str());


                        x = 2;

                       // std::chrono::nanoseconds interval(10000000);

                        // Adăugarea întârzierii
                        std::this_thread::sleep_for(interval);
                    }

                }
            }
            std::chrono::nanoseconds interval(10000000);

            // Adăugarea întârzierii
            std::this_thread::sleep_for(interval);

        }
    }

    //ClientConector::receive_message(socket);

   
        // Eliberăm statement-ul pentru a pregăti o nouă interogare
        ret = SQLFreeStmt(hStmt, SQL_CLOSE);

        // Re-alocăm handle-ul pentru a executa o nouă interogare pentru a selecta username-urile primilor numarUtilizatori utilizatori
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hStmt);


        // Construim interogarea SQL pentru a selecta primii numarUtilizatori utilizatori
        //  std::string cautare = "SELECT TOP " + std::to_string(10) + " username FROM users";
        //std::string cautare;
        if (x == 1)
            //cautare = "SELECT username FROM users WHERE id > " + std::to_string(nrAnterior) + " AND id <= " + std::to_string(nrAnterior + 10);
            cautare = "SELECT "+whatISelect+" FROM(SELECT*, ROW_NUMBER() OVER(ORDER BY id) AS RowNum FROM "+table+") AS UserWithRowNum WHERE RowNum > " + std::to_string(nrAnterior) + " AND  RowNum<=" + std::to_string(nrAnterior+10);
        //cautare = "SELECT username FROM users WHERE id > " + std::to_string(0) + " AND id <= " + std::to_string(10);
        else
            // cautare = "SELECT username FROM users WHERE id > " + std::to_string(nrAnterior);
            cautare = "SELECT " + whatISelect + " FROM(SELECT*, ROW_NUMBER() OVER(ORDER BY id) AS RowNum FROM " + table + ") AS UserWithRowNum WHERE RowNum > "+ std::to_string(nrAnterior);
        wide_query = converter.from_bytes(cautare);

        // Execută interogarea SQL
        ret = SQLExecDirect(hStmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);
        // Executăm interogarea SQL pentru a obține username-urile primilor numarUtilizatori utilizatori
        //ret = SQLExecDirect(hStmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            // Parcurgem fiecare rând rezultat
            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                // Citim numele de utilizator (username)
                for(int i=0;i< v.size();i++)
                { 
                 SQLCHAR username[255];
                ret = SQLGetData(hStmt, v[i], SQL_C_CHAR, username, sizeof(username), NULL);
                // Crearea unei durate de 50 de nanosecunde
                std::chrono::nanoseconds interval(10000000);

                // Adăugarea întârzierii
                std::this_thread::sleep_for(interval);
                // Afișăm numele de utilizator (username)
                std::cout << "Trimite " << username << std::endl;
                ClientConector::send_message(socket, reinterpret_cast<const char*>(username));

                std::this_thread::sleep_for(interval);
                //ClientConector::receive_message(socket);
                }
            }
            //SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }


        else {
            std::cerr << "Eroare la executarea interogării SELECT pentru username-uri" << std::endl;
        }

        // Eliberăm handle-ul statement-ului
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    

            
        
}

bool DbConector::executaProceduraStocata(const const SOCKET& socket, const std::string& proceduraStocata)
{
    //std::cout << "executa procedura";
    SQLHSTMT hstmt;
    SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    // Definește interogarea SQL utilizând un șir wide

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_query = converter.from_bytes(proceduraStocata);

    // Execută interogarea SQL
    retcode = SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);
    if (SQL_SUCCEEDED(retcode))
    {
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return true;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return false;
}

bool DbConector::cautaExistentaInTabel(const SOCKET& socket, const std::string& proceduraStocata)
{
    SQLHSTMT hstmt;

    SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    // Definește interogarea SQL utilizând un șir wide

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_query = converter.from_bytes(proceduraStocata);

    // Execută interogarea SQL
    retcode = SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);
    if (SQL_SUCCEEDED(retcode))
    {
        SQLCHAR resultMessage[20]; // Alocă spațiu pentru rezultatul mesajului
        SQLLEN cbResultMessage; // Lungimea rezultatului mesajului

        // Fetch rezultatul (doar o singură înregistrare este așteptată)
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_SUCCESS)
        {
            // Obține valoarea parametrului @resultMessage
            retcode = SQLGetData(hstmt, 1, SQL_C_CHAR, resultMessage, sizeof(resultMessage), &cbResultMessage);
            if (SQL_SUCCEEDED(retcode))
            {
                // Afisează mesajul (sau faci altceva cu el)
                std::cout << "Result message: " << resultMessage << std::endl;
                if (strcmp(reinterpret_cast<const char*>(resultMessage), "Username not found") == 0)
                {
                    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
                    return false;
                }
            }
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

        //return true;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return true;

}

bool DbConector::RequestToateIngredientele(const std::string& query, std::string& result) {
    SQLHSTMT hstmt;
    SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    // Definește interogarea SQL utilizând un șir wide
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_query = converter.from_bytes(query);

    // Execută interogarea SQL
    retcode = SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);

    if (SQL_SUCCEEDED(retcode)) {
        // Fetch and print the results
        SQLCHAR columnData1[255], columnData2[255], columnData3[255];
        SQLLEN indicator1, indicator2, indicator3;
        while (SQLFetch(hstmt) == SQL_SUCCESS) {
            SQLGetData(hstmt, 1, SQL_C_CHAR, columnData1, sizeof(columnData1), &indicator1);
            SQLGetData(hstmt, 2, SQL_C_CHAR, columnData2, sizeof(columnData2), &indicator2);
            SQLGetData(hstmt, 3, SQL_C_CHAR, columnData3, sizeof(columnData3), &indicator3);
                std::string str1((const char*)columnData1);
                std::string str2((const char*)columnData2);
                std::string str3((const char*)columnData3);
                result.append(str1 + " ");
                result.append(str2 + " ");
                result.append(str3 + "\n");
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return true;
    }
    else {
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return false;
    }
}

bool DbConector::RequestReteta(const std::string& query, std::string& result) {
    SQLHSTMT hstmt;
    SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    // Definește interogarea SQL utilizând un șir wide
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_query = converter.from_bytes(query);

    // Execută interogarea SQL
    retcode = SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);

    if (SQL_SUCCEEDED(retcode)) {
        // Fetch and print the results
        SQLCHAR columnData1[255], columnData2[255], columnData3[255];
        SQLLEN indicator1, indicator2, indicator3;
        while (SQLFetch(hstmt) == SQL_SUCCESS) {
            SQLGetData(hstmt, 1, SQL_C_CHAR, columnData1, sizeof(columnData1), &indicator1);
            SQLGetData(hstmt, 2, SQL_C_CHAR, columnData2, sizeof(columnData2), &indicator2);
            SQLGetData(hstmt, 3, SQL_C_CHAR, columnData3, sizeof(columnData3), &indicator3);
            std::string str1((const char*)columnData1);
            std::string str2((const char*)columnData2);
            std::string str3((const char*)columnData3);
            result.append(str1 + "\n");
            result.append(str2 + "\n");
            result.append(str3 + "\n");
            //int punct = result.find('.');
            //result[punct + 1] = 0;
            //result.append(str3 + "\n");
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return true;
    }
    else {
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return false;
    }
}

bool DbConector::RequestIngrediente(const std::string& query, std::string& result) {
    SQLHSTMT hstmt;
    SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    // Definește interogarea SQL utilizând un șir wide
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_query = converter.from_bytes(query);

    // Execută interogarea SQL
    retcode = SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);

    if (SQL_SUCCEEDED(retcode)) {
        // Fetch and print the results
        SQLCHAR columnData1[255], columnData2[255], columnData3[255];
        SQLLEN indicator1, indicator2, indicator3;
        while (SQLFetch(hstmt) == SQL_SUCCESS) {
            SQLGetData(hstmt, 1, SQL_C_CHAR, columnData1, sizeof(columnData1), &indicator1);
            SQLGetData(hstmt, 2, SQL_C_CHAR, columnData2, sizeof(columnData2), &indicator2);
            SQLGetData(hstmt, 3, SQL_C_CHAR, columnData3, sizeof(columnData3), &indicator3);
            std::string str1((const char*)columnData1);
            std::string str2((const char*)columnData2);
            std::string str3((const char*)columnData3);
            result.append(str1 + " ");
            result.append(str2 + " ");
            result.append(str3 + "\n");
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return true;
    }
    else {
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return false;
    }
}

bool DbConector::RequestCumparaturi(const std::string& query, std::string& result, int cantitate, double& pret)
{
    SQLHSTMT hstmt;
    SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    // Definește interogarea SQL utilizând un șir wide
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_query = converter.from_bytes(query);

    // Execută interogarea SQL
    retcode = SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);

    if (SQL_SUCCEEDED(retcode)) {
        // Fetch and print the results
        SQLCHAR columnData1[255], columnData2[255], columnData3[255], columnData4[255];
        SQLLEN indicator1, indicator2, indicator3, indicator4;
        while (SQLFetch(hstmt) == SQL_SUCCESS) {
            SQLGetData(hstmt, 1, SQL_C_CHAR, columnData1, sizeof(columnData1), &indicator1);
            SQLGetData(hstmt, 2, SQL_C_CHAR, columnData2, sizeof(columnData2), &indicator2);
            SQLGetData(hstmt, 3, SQL_C_CHAR, columnData3, sizeof(columnData3), &indicator3);
            SQLGetData(hstmt, 4, SQL_C_CHAR, columnData4, sizeof(columnData4), &indicator4);
            std::string str1((const char*)columnData1);
            double temp = std::stod(str1);
            temp *= 2;
            pret += temp;
            str1.clear();
            str1 = std::to_string(temp);
            std::string str2((const char*)columnData2);
            std::string str3((const char*)columnData3);
            std::string str4((const char*)columnData4);
            result.append(str1 + " lei, ");
            result.append(str2 + " zile livrare ");
            result.append(str3 + " calitate ");
            result.append(str4 + "\n");
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return true;
    }
    else {
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return false;
    }
}

bool DbConector::RequestToateRetetele(std::string& result) {
    SQLHSTMT hstmt;
    SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    // Definește interogarea SQL pentru apelul procedurii stocate



    // Execută interogarea SQL pentru apelul procedurii stocate
    std::string queryMaxIdRetete = "EXEC RequestIdMaxRetete";
    int MaxIdretete;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converterMax;
    std::wstring wide_queryMax = converterMax.from_bytes(queryMaxIdRetete);

    // Execută interogarea SQL

    retcode = SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_queryMax.c_str())), SQL_NTS);

    if (SQL_SUCCEEDED(retcode))
    {
        SQLCHAR IDColumnData1[255];
        SQLLEN IDIndicator1;
        while (SQLFetch(hstmt) == SQL_SUCCESS)
        {
            SQLGetData(hstmt, 1, SQL_C_CHAR, IDColumnData1, sizeof(IDColumnData1), &IDIndicator1);
            if (IDIndicator1 != SQL_NULL_DATA)
            {
                std::string str1((const char*)IDColumnData1);
                MaxIdretete = std::stoi(str1);
                //std::cout << " " << MaxIdretete << "\n";
                result.append(str1);
                result.append("\n_\n");
            }
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }
    else {
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return false;
    }

    for (int i = 1; i <= MaxIdretete; i++)
    {
        //EXEC RequestRetetaFromID
        //EXEC RequestIngredienteRetetaFromID
        std::string queryReteta = "EXEC RequestRetetaFromID ";
        std::string Reteta;
        DbConector::RequestReteta(queryReteta + std::to_string(i), Reteta);
        //std::cout << Reteta;
        result.append(Reteta);
        std::string queryIngrediente = "RequestIngredienteRetetaFromID ";
        std::string Ingrediente;
        DbConector::RequestIngrediente(queryIngrediente + std::to_string(i), Ingrediente);
        //std::cout << Ingrediente;
        result.append(Ingrediente);
        result.append("_\n");
    }
    std::cout << "\n" << result;
}


bool DbConector::RequestActivity(const std::string& query, std::string& result)
{
    SQLHSTMT hstmt;
    SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    // Definește interogarea SQL utilizând un șir wide
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_query = converter.from_bytes(query);

    // Execută interogarea SQL
    retcode = SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);

    if (SQL_SUCCEEDED(retcode)) {
        // Fetch and print the results
        SQLCHAR columnData1[255], columnData2[255], columnData3[255];
        SQLLEN indicator1, indicator2, indicator3;
        while (SQLFetch(hstmt) == SQL_SUCCESS) {
            SQLGetData(hstmt, 1, SQL_C_CHAR, columnData1, sizeof(columnData1), &indicator1);
            SQLGetData(hstmt, 2, SQL_C_CHAR, columnData2, sizeof(columnData2), &indicator2);
            std::string str1((const char*)columnData1);
            std::string str2((const char*)columnData2);
            result.append(str1 + " ");
            result.append(str2 + "\n");
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return true;
    }
    else {
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return false;
    }
}