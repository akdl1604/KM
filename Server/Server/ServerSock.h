//ServerSock.h
/*
* �ɹ�����
* ������&�Ҹ���
* Get&Set �޼���
* ��� �޼���
*/

#pragma once

class ServerSock 
{
private:
	SOCKET listenSocket;

	//�Լ� ������(callback �Լ��� ����)
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