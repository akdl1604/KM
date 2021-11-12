// ClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "Server.h"
#include "ServerDlg.h"
#include "ClientSocket.h"
#include "ListenSocket.h"
#include "LogManager.h"


// CClientSocket

CClientSocket::CClientSocket()
{
	m_pListenSocket = NULL;
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수
void CClientSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSocket = pSocket;
}

void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CSocket::OnClose(nErrorCode);

	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString strTmp = _T("");
	CString strIPAdress = _T("");
	UINT uPortNumber = 0;
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	GetPeerName(strIPAdress, uPortNumber);
	if (Receive(szBuffer, sizeof(szBuffer)) > 0)
	{		
		CServerDlg* pMain = (CServerDlg*)AfxGetMainWnd();
		strTmp.Format(_T("[%s:%d] : %s"), strIPAdress, uPortNumber, szBuffer);
		pMain->m_List.AddString(strTmp);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);

		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->SendChatDataAll(szBuffer);
	}
	CSocket::OnReceive(nErrorCode);
	LogManager::GetInstance()->Receive("");
}
