#pragma once

#if !defined(_LOGMANAGER_H_)
#define _LOGMANAGER_H_
#endif


#include "afx.h"
#include "ClientDlg.h"
#include "ConnectSocket.h"


class LogManager{
public:
	~LogManager(void);
	void LogConnect(LPCSTR  mesg, ... );
	void LogDisconnect(LPCSTR  mesg, ...);
	void Send(LPCSTR  mesg, ...);
	static LogManager * GetInstance();

protected:
	LogManager();
	CStdioFile * Open();
	void	Close();

	static LogManager * me;
	static BOOL instanceFlag;
	CStdioFile * logFile;
};
