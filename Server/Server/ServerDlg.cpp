
// ServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerDlg 대화 상자

CServerDlg* g_pMainDlg;

void LogMessage(int type, TCHAR* msg)
{
	CString str_Sock, str_Result;
	if (type == 0)
		str_Sock.Format("[오류] %s\n", msg);
	else if (type == 1)
		str_Sock.Format("%s\n", msg);        //서버실행
	else if (type == 2)
		str_Sock.Format("[클라이언트 접속] %s\n", msg);
	else if (type == 3)
		str_Sock.Format("[클라이언트 해제] %s\n", msg);
	else if (type == 4)
		str_Result.Format("[데이터 수신] %s\n", msg);
	else if (type == 5)
		str_Result.Format("[데이터 송신] %s\n", msg);

	//	g_pMainDlg->SetWindowText(str);

		//::SendMessage(g_pMainDlg->m_ctrlList1.m_hWnd, LB_ADDSTRING, (LPARAM)str.GetBuffer(), 0);
	g_pMainDlg->m_ctrlListSock.AddString(str_Sock);
	g_pMainDlg->m_ctrlListResult.AddString(str_Result);
}

void RecvMessage(TCHAR* msg)
{

}


CServerDlg::CServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pServer = new ServerSock(LogMessage, RecvMessage);

	g_pMainDlg = this;
}

CServerDlg::~CServerDlg()
{
	delete pServer;
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlListSock);
	DDX_Control(pDX, IDC_LIST3, m_ctrlListResult);
	DDX_Control(pDX, IDC_RESULT_TAB1, m_Result_Tab);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CServerDlg::OnTcnSelchangeTab1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_RESULT_TAB1, &CServerDlg::OnTcnSelchangeResultTab1)
END_MESSAGE_MAP()


// CServerDlg 메시지 처리기

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	m_Result_Tab.InsertItem(0, "Statistics");
	m_Result_Tab.InsertItem(1, "S/F");
	m_Result_Tab.SetCurSel(0);
	CRect rc;
	
	m_Result_Tab.GetWindowRect(rc);
	
	pDlg1 = new CTab1; //Tab1추가
	
	pDlg1->Create(IDD_Tab1, &m_Result_Tab); // m_Result_Tab에 생성
	pDlg1->MoveWindow(0, 20, rc.Width(), rc.Height()); //크기조절
	pDlg1->ShowWindow(SW_SHOW); //표시	

	//pServer->Start(9000);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CServerDlg::OnTcnSelchangeResultTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (IDC_TAB1 == pNMHDR->idFrom)
	{
		int iSelect = m_Result_Tab.GetCurSel(); // 선택한 위치 확인

		switch (iSelect) {
		case 0:
			pDlg1->ShowWindow(SW_SHOW);
			break;
		case 1:
			pDlg1->ShowWindow(SW_HIDE);
			break;
		}

	}
	*pResult = 0;
}
