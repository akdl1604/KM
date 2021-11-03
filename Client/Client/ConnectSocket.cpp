// ConnectSocket.cpp: 구현 파일
//

#include "pch.h"
#include "Client.h"
#include "ClientDlg.h"
#include "ConnectSocket.h"


// CConnectSocket

CConnectSocket::CConnectSocket()
{
}

CConnectSocket::~CConnectSocket()
{
}


// CConnectSocket 멤버 함수

void CConnectSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CSocket::OnClose(nErrorCode);
	AfxMessageBox(L"ERROR: Disconnected from server!");
	::PostQuitMessage(0);
	ShutDown();
	Close();
}


void CConnectSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	if (Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		CClientDlg* pMain = (CClientDlg*)AfxGetMainWnd();
	}
	CSocket::OnReceive(nErrorCode);
}