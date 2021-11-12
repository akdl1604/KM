#pragma once

// CClientSocket 명령 대상

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	void SetListenSocket(CAsyncSocket* pSocket);

	CAsyncSocket* m_pListenSocket;
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


