#pragma once


// CMyDialog

class CMyDialog : public CWnd
{
	DECLARE_DYNAMIC(CMyDialog)

public:
	CMyDialog();
	virtual ~CMyDialog();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CString user;
};


