#pragma once

// CListenSocket 명령 대상

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	CPtrList m_ptrClientSocketList;
	CPtrList m_ptrLogList;
	virtual void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pClient);
	void SendChatDataAll(TCHAR* pszMessage);
};


