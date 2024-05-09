#pragma once
#include "Sign.h"
class Login :public Sign
{
public:
	Login(SOCKET socket ) :Sign(socket){};
	//void play() { std::cout << 1<<"\n\n"; }
	//void startThread() override {  // Transmiți metoda startThread ca pointer la funcție către constructorul std::thread
	//	std::thread(&Login::play, this).join();
	//}
	void play();// { std::cout << 2 << "\n\n"; }
	~Login(){};
};

