#pragma once
#include<iostream>
#include<vector>
#include<thread>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
class ISign
{
public:
	virtual void startThread() = 0;
};

