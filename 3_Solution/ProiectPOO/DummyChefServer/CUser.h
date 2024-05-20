#pragma once
#include"IUser.h"
class CUser: public IUser
{
protected:
	SOCKET socket;
	std::thread myth;
	bool b;
public:
	CUser(SOCKET socket);
	const SOCKET getSocket() const {
		return socket;
	}
	virtual void play();
	void startThread() override {

		myth = std::move(std::thread(&CUser::play, this));
		myth.detach();
	}
	~CUser() { socket = INVALID_SOCKET;
	b = false;         
	// Verifică dacă thread-ul este încă în desfășurare

	if (myth.joinable()) {
		// Așteaptă ca thread-ul să se termine
		myth.join();
	}
	};

};

