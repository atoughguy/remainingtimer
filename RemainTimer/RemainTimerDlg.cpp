
// RemainTimerDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "RemainTimer.h"
#include "RemainTimerDlg.h"
#include "afxdialogex.h"
#include "FullScreenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRemainTimerDlg 대화 상자



CRemainTimerDlg::CRemainTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REMAINTIMER_DIALOG, pParent)
	, m_strFilePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRemainTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HOUR, m_idcHour);
	DDX_Control(pDX, IDC_MIN, m_idcMin);
	DDX_Control(pDX, IDC_SEC, m_idcSec);
}

BEGIN_MESSAGE_MAP(CRemainTimerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILE_OPEN, &CRemainTimerDlg::OnBnClickedFileOpen)
	ON_BN_CLICKED(IDOK, &CRemainTimerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRemainTimerDlg 메시지 처리기

BOOL CRemainTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CString strTitle = _T("Remaining Timer");
	CString strVersion = _T("0.0.0.1");
	SetWindowText(strTitle + " " + strVersion);

	m_idcHour.LimitText(2);
	m_idcMin.LimitText(2);
	m_idcSec.LimitText(2);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRemainTimerDlg::OnPaint()
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
HCURSOR CRemainTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRemainTimerDlg::OnBnClickedFileOpen()
{
	// TODO: Add your control notification handler code here
	static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP, *.GIF, *.JPG | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif | 모든파일(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("*.jpg"), _T(""), OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal())
	{
		m_strFilePath = dlg.GetPathName();
		SetDlgItemText(IDC_FILE_PATH, m_strFilePath);
	}
}


void CRemainTimerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	CFullScreenDlg childDlg(this);
	CString strHour = _T("");
	CString strMin = _T("");
	CString strSec = _T("");

	GetDlgItemText(IDC_HOUR, strHour);
	GetDlgItemText(IDC_MIN, strMin);
	GetDlgItemText(IDC_SEC, strSec);

	if (strHour == "" || _ttoi(strHour) > 24 || _ttoi(strHour) < 0)
	{
		MessageBox(_T("Plesae insert hour(0~24)"));
		return;
	}
	if (strMin == "" || _ttoi(strMin) > 59 || _ttoi(strMin) < 0)
	{
		MessageBox(_T("Plesae insert minute(0~59)"));
		return;
	}
	if (strSec == "" || _ttoi(strSec) > 59 || _ttoi(strSec) < 0)
	{
		MessageBox(_T("Plesae insert second(0~59)"));
		return;
	}

	childDlg.m_strFilePath = m_strFilePath;
	childDlg.m_strSetHour = strHour;
	childDlg.m_strSetMin = strMin;
	childDlg.m_strSetSec = strSec;

	// create child dialog
	childDlg.DoModal();

	// destroy the child dialog
	childDlg.DestroyWindow();
}
