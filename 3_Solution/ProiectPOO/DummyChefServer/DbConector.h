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
	static void cautaViewRequesturi(const SOCKET& socket, int nrAnterior, std::string whatISelect,const std::string table,std::vector<int>v);
	static bool executaProceduraStocata(const SOCKET& socket, const std::string& proceduraStocata) ;
	static bool cautaExistentaInTabel(const SOCKET& socket, const std::string& proceduraStocata);

	static bool RequestToateIngredientele(const std::string& query, std::string& result);
	static bool RequestReteta(const std::string& query, std::string& result);
	static bool RequestIngrediente(const std::string& query, std::string& result);
	static bool RequestToateRetetele(std::string& result);
	static bool RequestCumparaturi(const std::string& query, std::string& result, int cantitate, double& pret);

	static bool RequestActivity(const std::string& query, std::string& result);


};

