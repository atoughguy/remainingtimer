#pragma once
#include "afxwin.h"


// CFullScreenDlg dialog

class CFullScreenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFullScreenDlg)

public:
	CFullScreenDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFullScreenDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FULL_SCREEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CWnd* m_pParentWnd;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CStatic m_iSetHour;
	CString m_strSetHour;
	virtual BOOL OnInitDialog();
	CString m_strSetMin;
	CString m_strSetSec;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void calcTime();
	CString m_strFilePath;
	//afx_msg void OnPaint();
	CRect m_rectSize;
};
