
// Bjy_HexTriSView.h : CBjy_HexTriSView Ŭ������ �������̽�
//

#pragma once
#pragma comment(lib, "winmm")
#include <MMSystem.h>
#include "resource.h"
#include "atltypes.h"


class CBjy_HexTriSView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CBjy_HexTriSView();
	DECLARE_DYNCREATE(CBjy_HexTriSView)

public:
	enum{ IDD = IDD_Bjy_HexTriS_FORM };

// Ư���Դϴ�.
public:
	CBjy_HexTriSDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	int arr[13][9];
	int unit[6][13][9];
	int temp[6][13][9];
// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CBjy_HexTriSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void newUNIT(int val);
	int m_iNowX;
	int m_iNowY;
	CPoint p;
	bool check;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_iNowBlockDir;
	void clearUNIT(void);
	BOOL canMove(int dir, int x, int y);
	void tempUNIT(int val, int x, int y);
	void tempClear(void);
	int m_iNowBlockShape;
	void stackBlock(int val);
	void LineCheck(void);
	bool IsGameEnd(void);
	void GameStart(void);
	int m_iScore;
	int iRemoveLineCount;
	CString str;
	void SetGameEND(void);
	int LineNum(void);
	bool pauseCheck;
	CString rank;
	CString m_userName;
	afx_msg void OnGameNew();
};

#ifndef _DEBUG  // Bjy_HexTriSView.cpp�� ����� ����
inline CBjy_HexTriSDoc* CBjy_HexTriSView::GetDocument() const
   { return reinterpret_cast<CBjy_HexTriSDoc*>(m_pDocument); }
#endif

