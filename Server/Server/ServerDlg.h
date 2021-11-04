﻿
// ServerDlg.h: 헤더 파일
//

#pragma once
#include "CTab1.h"

// CServerDlg 대화 상자
class CServerDlg : public CDialogEx
{
// 생성입니다.
private:
	ServerSock* pServer;
public:
	CServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	~CServerDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ctrlListSock;
	CListBox m_ctrlListResult;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTcnSelchangeResultTab1(NMHDR* pNMHDR, LRESULT* pResult);
	CTab1* pDlg1;
	CTabCtrl m_Result_Tab;
};
