//ServerSock.h
/*
* 맴버변수
* 생성자&소멸자
* Get&Set 메서드
* 기능 메서드
*/

#pragma once


#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

class ServerSock
{
private:
	SOCKET listenSocket;

	//함수 포인터(callback 함수의 역할)
private:
	unsigned int __stdcall sock_ListenThread(void* value);
	unsigned int __stdcall WorkThread(void* value);

public:
	ServerSock(void (*Fun1)(int, TCHAR*), void(*Fun2)(TCHAR*));
	~ServerSock();

public:
	void sock_LibInit();
	void sock_LibExit();
	void sock_CreateSocket();
	void DisplayMessage();
private:
	int Recv(SOCKET sock, SOCKADDR_IN clientaddr, char* buf);
	int Send(SOCKET sock, const char* buf, int datasize);
	int recvn(SOCKET s, char* buf, int len, int flags);

	SOCKET Accept(SOCKADDR_IN* addr);
	
};