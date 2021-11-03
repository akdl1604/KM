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
	void (*LogMessage)(int, TCHAR*);
	void (*RecvMessage)(TCHAR*);

public:
	ServerSock(void (*Fun1)(int, TCHAR*), void(*Fun2)(TCHAR*));
	~ServerSock();

public:
	bool Start(int port);

private:
	bool InnerStart(int port);
	static DWORD _stdcall ListenThread(LPVOID data);
};