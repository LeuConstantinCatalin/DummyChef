﻿#include "DbConector.h"
#include "ClientConector.h"
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
    SQLHSTMT hstmt;
    SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    // Definește interogarea SQL utilizând un șir wide

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_query = converter.from_bytes(cautare);

    // Execută interogarea SQL
    retcode= SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);
    if (SQL_SUCCEEDED(retcode))
    {
   
        return true;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return false;
}


    ///////////////
#include <sstream>

bool DbConector::executeQuery(const std::string& query, std::string& result) {
    SQLHSTMT hstmt;
    SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    // Definește interogarea SQL utilizând un șir wide
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_query = converter.from_bytes(query);

    // Execută interogarea SQL
    retcode = SQLExecDirect(hstmt, reinterpret_cast<SQLWCHAR*>(const_cast<wchar_t*>(wide_query.c_str())), SQL_NTS);

    if (SQL_SUCCEEDED(retcode)) {
        // Fetch and store the results in a string
        std::ostringstream oss;
        SQLCHAR columnData1[255], columnData2[255], columnData3[255];
        SQLLEN indicator1, indicator2, indicator3;
        while (SQLFetch(hstmt) == SQL_SUCCESS) {
            SQLGetData(hstmt, 1, SQL_C_CHAR, columnData1, sizeof(columnData1), &indicator1);
            SQLGetData(hstmt, 2, SQL_C_CHAR, columnData2, sizeof(columnData2), &indicator2);
            SQLGetData(hstmt, 3, SQL_C_CHAR, columnData3, sizeof(columnData3), &indicator3);
            if (indicator1 != SQL_NULL_DATA && indicator2 != SQL_NULL_DATA && indicator3 != SQL_NULL_DATA) {
                oss << "\n" << columnData1 << "\n" << columnData2 << "\n" << columnData3 << std::endl;
            }
        }
        result = oss.str();

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return true;
    }
    else {
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return false;
    }
}
