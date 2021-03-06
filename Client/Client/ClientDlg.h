
// ClientDlg.h: 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "ConnectSocket.h"

// CClientDlg 대화 상자
class CClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CConnectSocket m_Socket;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
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
	CListBox m_List;
	CListBox m_ptrConnect;

public:
	afx_msg void OnClose();
	CEdit m_Edit;
	afx_msg void OnBnClickedButton2();
};
