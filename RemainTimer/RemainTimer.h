
// RemainTimer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CRemainTimerApp:
// �� Ŭ������ ������ ���ؼ��� RemainTimer.cpp�� �����Ͻʽÿ�.
//

class CRemainTimerApp : public CWinApp
{
public:
	CRemainTimerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CRemainTimerApp theApp;