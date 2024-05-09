#pragma once
#include"IUser.h"
class CUser: public IUser
{
protected:
	SOCKET socket;
	bool t;
public:
	CUser(SOCKET socket);
	virtual void play();
	void startThread() override {
		std::thread myth = std::move(std::thread(&CUser::play, this));
		if (t == true)
			myth.detach();
		//play();
		else
			myth.join();
	}
	~CUser() {};
};

