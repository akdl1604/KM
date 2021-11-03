//WbServer.cpp

#include "pch.h"
#include <tchar.h>
#include <exception>

using namespace std;

ServerSock::ServerSock(void (*Fun1)(int, TCHAR*), void(*Fun2)(TCHAR*))
    : listenSocket(0), LogMessage(Fun1), RecvMessage(Fun2)
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        exit(0);
    }

}

ServerSock::~ServerSock()
{
    WSACleanup();
}

bool ServerSock::Start(int port)
{
    if (InnerStart(port) == false)
        return false;

    //다음 단계로
    CloseHandle(CreateThread(0, 0, ListenThread, this, 0, 0));

    return true;
}

bool ServerSock::InnerStart(int port)
{
    try
    {
        //socket() -> bind() -> listen()
        listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (listenSocket == INVALID_SOCKET)
            return false;

        SOCKADDR_IN ServerAddr = { 0 };
        ZeroMemory(&ServerAddr, sizeof(ServerAddr));    //Win32API
        ServerAddr.sin_family = AF_INET;
        ServerAddr.sin_port = htons(port);
        ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);      //(ULONG)0x00000000 (정수)
        int retval = bind(listenSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));

        if (retval == SOCKET_ERROR)
            return false;
        retval = listen(listenSocket, SOMAXCONN); //0x7fffffff
        if (retval == SOCKET_ERROR)
            return false;
        return true;
    }
   
    catch(exception e)
    {
        TEXT(e.what());
    }
    
  
}

//static 메서드는 this 사용 불가(인스턴스 맴버 접근 불가)
//static은 static맴버(클래스 맴버)만 접근 가능
DWORD _stdcall ServerSock::ListenThread(LPVOID data)
{
    ServerSock* pServer = (ServerSock*)data;
    SOCKET listenSocket = pServer->listenSocket;

    pServer->LogMessage(1, (TCHAR*)TEXT("[서버 실행]"));  //서버실행

    char buf[100];
    TCHAR LogBuff[100];
    while (true)
    {
        SOCKADDR_IN ClientAddr = { 0 };
        int clinetaddrsize = sizeof(ClientAddr);        //<----------
        SOCKET ClientSocket = accept(listenSocket, (SOCKADDR*)&ClientAddr, &clinetaddrsize);
        if (ClientSocket == INVALID_SOCKET)
            return -1;

        //2) 클라이언트 접속 정보 출력
        wsprintf(LogBuff, TEXT("%s:%d"), inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));
        pServer->LogMessage(2, LogBuff);    //접속.

        while (true)
        {
            //3) recv
            int rev = recv(ClientSocket, buf, sizeof(buf), 0);
            if (rev == SOCKET_ERROR)
            {
                pServer->LogMessage(0, (TCHAR*)TEXT("소켓에 오류가 발생"));
                break;
            }
            else if (rev == 0)
            {
                break;
            }
            else
            {
                wsprintf(LogBuff, TEXT("%s:%d, %dbyte"),
                    inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port), rev);
                pServer->LogMessage(4, LogBuff);    //수신

                wsprintf(LogBuff, TEXT("[%s:%d] %s"),
                    inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port), buf);
                pServer->RecvMessage(LogBuff);

                //--------------------------------------------------------------------------
                rev = send(ClientSocket, buf, rev, 0);      //<---------------

                wsprintf(LogBuff, TEXT("%s:%d, %dbyte"),
                    inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port), rev);
                pServer->LogMessage(5, LogBuff);    //송신
            }
        }

        wsprintf(LogBuff, TEXT("%s:%d"), inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));
        pServer->LogMessage(3, LogBuff);    //해제

        closesocket(ClientSocket);
    }
    return 0;
}