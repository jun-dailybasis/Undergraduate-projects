
// Bjy_HexTriS.h : Bjy_HexTriS ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CBjy_HexTriSApp:
// �� Ŭ������ ������ ���ؼ��� Bjy_HexTriS.cpp�� �����Ͻʽÿ�.
//

class CBjy_HexTriSApp : public CWinApp
{
public:
	CBjy_HexTriSApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBjy_HexTriSApp theApp;
