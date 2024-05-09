#pragma once
#include<iostream>
#include "ClientConector.h"
#include <Windows.h>
#include <sqltypes.h>

#include <tchar.h>
#include <sql.h>
#include <sqlext.h>
#include <codecvt>

#pragma comment (lib, "odbc32.lib")

class DbConector
{

private:
	//SQLHENV henv;
	static SQLHDBC hdbc;
	//SQLRETURN retcode;

	static DbConector* instance;
	 DbConector(){};
     ~DbConector(){};
	
public:

	static DbConector& createDbConector();
	static void deleteDbConector();
	static void initializareConexiuneBd();
	static bool efectueazaCautareUserInDb(const std::string& cautare, const std::string& username, const std::string& parola, const std::string&userType, SOCKET& socket) ;
	static bool insereazaUserInDb(const std::string& cautare, SOCKET& socket);

};

