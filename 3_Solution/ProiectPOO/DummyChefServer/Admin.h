#pragma once
#include "Bucatar.h"
class Admin :public Bucatar
{
public:
	Admin(SOCKET sock) :Bucatar(sock) {};
	void play()override;

};

