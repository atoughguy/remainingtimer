
// RemainTimerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "RemainTimer.h"
#include "RemainTimerDlg.h"
#include "afxdialogex.h"
#include "FullScreenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRemainTimerDlg ��ȭ ����



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


// CRemainTimerDlg �޽��� ó����

BOOL CRemainTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CString strTitle = _T("Remaining Timer");
	CString strVersion = _T("0.0.0.1");
	SetWindowText(strTitle + " " + strVersion);

	m_idcHour.LimitText(2);
	m_idcMin.LimitText(2);
	m_idcSec.LimitText(2);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CRemainTimerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CRemainTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRemainTimerDlg::OnBnClickedFileOpen()
{
	// TODO: Add your control notification handler code here
	static TCHAR BASED_CODE szFilter[] = _T("�̹��� ����(*.BMP, *.GIF, *.JPG | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif | �������(*.*)|*.*||");
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
