#pragma once
#include"CUser.h"

class Utilizator: public CUser
{
public:
	Utilizator(SOCKET socket) :CUser(socket) {};
	void play()override;
	~Utilizator() {};
};

