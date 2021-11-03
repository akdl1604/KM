﻿// CConnectSocket.cpp: 구현 파일
//

#include "pch.h"
#include "Client.h"
#include "ClientDlg.h"
#include "ConnectSocket.h"
#include "LogManager.h"


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
	LogManager::GetInstance()->LogDisconnect("Put Your Log Here!!");
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
		pMain->m_List.AddString(szBuffer); // 리스트에 문자열을 추가한다.
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
	}
	CSocket::OnReceive(nErrorCode);
}
