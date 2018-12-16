// FullScreenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FullScreenDlg.h"
#include "afxdialogex.h"
#include "RemainingTimer.h"
#include "RemainingTimerDlg.h"
#include <atlimage.h>


// CFullScreenDlg dialog

IMPLEMENT_DYNAMIC(CFullScreenDlg, CDialogEx)

CFullScreenDlg::CFullScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FULL_SCREEN, pParent)
	, m_strSetHour(_T(""))
	, m_strSetMin(_T(""))
	, m_strSetSec(_T(""))
	, m_strFilePath(_T(""))
{
	m_pParentWnd = pParent;
}

CFullScreenDlg::~CFullScreenDlg()
{
}

void CFullScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SET_HOUR, m_iSetHour);
	DDX_Control(pDX, IDC_COMPANY_LOGO, m_picCompLogo);
}


BEGIN_MESSAGE_MAP(CFullScreenDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CFullScreenDlg message handlers


int CFullScreenDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	
	long style = ::GetWindowLong(m_hWnd, GWL_STYLE);

	style &= ~WS_CAPTION;
	style &= ~WS_SYSMENU;

	::SetWindowLong(m_hWnd, GWL_STYLE, style);

	int screenx = GetSystemMetrics(SM_CXSCREEN);
	int screeny = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(NULL, -4, -4, screenx + 8, screeny + 4, SWP_NOZORDER);
	
	// ShowWindow(SW_SHOWMAXIMIZED);
	return 0;
}


BOOL CFullScreenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetDlgItemText(IDC_SET_HOUR, m_strSetHour);
	SetDlgItemText(IDC_SET_MIN, m_strSetMin);
	SetDlgItemText(IDC_SET_SEC, m_strSetSec);

	setControlFont();

	setControlPosition();

	// timer on
	SetTimer(8, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CFullScreenDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case 8:
		setCompanyLogo();
		calcTime();
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CFullScreenDlg::calcTime()
{
	int ihour = _ttoi(m_strSetHour);
	int imin = _ttoi(m_strSetMin);
	int isec = _ttoi(m_strSetSec);

	if (ihour > 0) {
		if (imin == 0 && isec == 0) { // ex. 1:0:0
			ihour--;
			imin = 59;
			isec = 59;
		}
		else if (imin < 60 && imin > -1) { // 초만 감소시킬 때
			isec--;
			
			if (isec < 0) { // 59~0분일 때 0초 다음 59초로 변경
				isec = 59;

				if (imin < 60 && imin > 0) // 0초 다음 59초로 변경됐을 때 분도 감소
					imin--;
			}
		}
	}
	else { // ihour == 0
		if (imin < 60 && imin > 0) { // 59~1분일 때 초 감소
			isec--;

			if (isec < 0) { // 59~1분일 때 0초 다음 59초로 변경
				isec = 59;

				if (imin < 60 && imin > 0) // 0초 다음 59초로 변경됐을 때 분도 감소
					imin--;
			}
		}
		else { // 0분일 때 초만 감소
			if (isec < 60 && isec > 0)
				isec--;
		}
	}
	
	m_strSetHour.Format(_T("%d"), ihour);
	m_strSetMin.Format(_T("%d"), imin);
	m_strSetSec.Format(_T("%d"), isec);

	SetDlgItemText(IDC_SET_HOUR, m_strSetHour);
	SetDlgItemText(IDC_COLON_1, _T(":"));
	SetDlgItemText(IDC_SET_MIN, m_strSetMin);
	SetDlgItemText(IDC_COLON_2, _T(":"));
	SetDlgItemText(IDC_SET_SEC, m_strSetSec);

	if (ihour == 0 && imin == 0 && isec == 0)
		KillTimer(8);
}

/*
void CFullScreenDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages

					   // set logo file
	CClientDC dc(this);
	CImage Image;

	if (m_strFilePath != "") {
		Image.Load(m_strFilePath);
		Image.BitBlt(dc.m_hDC, 10, 10);
	}
	else {
		Image.IsNull();
	}
}
*/

void CFullScreenDlg::setControlFont()
{
	// set idc control font
	m_idcFont.CreateFont(500, // height
		200, // width
		0,
		0,
		1, // weight
		0,
		0,
		0,
		0,
		OUT_DEFAULT_PRECIS,
		0,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		_T("굴림"));

	// set colon control font
	m_colonFont.CreateFont(300, // height
		80, // width
		0,
		0,
		1, // weight
		0,
		0,
		0,
		0,
		OUT_DEFAULT_PRECIS,
		0,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		_T("굴림"));

	GetDlgItem(IDC_SET_HOUR)->SetFont(&m_idcFont);
	GetDlgItem(IDC_SET_MIN)->SetFont(&m_idcFont);
	GetDlgItem(IDC_SET_SEC)->SetFont(&m_idcFont);
	GetDlgItem(IDC_COLON_1)->SetFont(&m_colonFont);
	GetDlgItem(IDC_COLON_2)->SetFont(&m_colonFont);
}


void CFullScreenDlg::setControlPosition()
{
	RECT rc1;
	::GetWindowRect(this->m_hWnd, &rc1);	// get dialog size
											// set location of idc controls
	int idcSetHourX = (rc1.right / 2) / 6;
	int idcSetMinX = (rc1.right / 2) - (rc1.right / 10);
	int idcSetSecX = (rc1.right / 2) + (rc1.right / 5);
	int idcColon1X = ((rc1.right / 2) / 2) + (rc1.right / 12);
	int idcColon2X = (rc1.right / 2) + (rc1.right / 7);
	int idcSetY = (rc1.bottom / 2) - (rc1.bottom / 5);
	int idcColonY = (rc1.bottom / 3) + (rc1.bottom / 12);
	// width, height
	int idcWidth = 450;
	int idcHeight = 600;
	int colonWidth = 80;
	int colonHeight = 600;

	// move idc controls
	GetDlgItem(IDC_SET_HOUR)->MoveWindow(idcSetHourX, idcSetY, idcWidth, idcHeight);
	GetDlgItem(IDC_COLON_1)->MoveWindow(idcColon1X, idcColonY, colonWidth, colonHeight);
	GetDlgItem(IDC_SET_MIN)->MoveWindow(idcSetMinX, idcSetY, idcWidth, idcHeight);
	GetDlgItem(IDC_COLON_2)->MoveWindow(idcColon2X, idcColonY, colonWidth, colonHeight);
	GetDlgItem(IDC_SET_SEC)->MoveWindow(idcSetSecX, idcSetY, idcWidth, idcHeight);
}


int CFullScreenDlg::setCompanyLogo()
{
	CWnd *pWnd = (CWnd *)GetDlgItem(IDC_COMPANY_LOGO);
	CDC *dc = pWnd->GetDC();
	CStatic *pstatic = (CStatic *)GetDlgItem(IDC_COMPANY_LOGO);
	CRect rect;

	pstatic->GetClientRect(rect);
	m_bmpBitmap.Load(m_strFilePath);
	m_bmpBitmap.Draw(dc->m_hDC, 0, 0, m_bmpBitmap.GetWidth(), m_bmpBitmap.GetHeight());
	
	return 0;
}