
// Bjy_HexTriSView.h : CBjy_HexTriSView 클래스의 인터페이스
//

#pragma once
#pragma comment(lib, "winmm")
#include <MMSystem.h>
#include "resource.h"
#include "atltypes.h"


class CBjy_HexTriSView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CBjy_HexTriSView();
	DECLARE_DYNCREATE(CBjy_HexTriSView)

public:
	enum{ IDD = IDD_Bjy_HexTriS_FORM };

// 특성입니다.
public:
	CBjy_HexTriSDoc* GetDocument() const;

// 작업입니다.
public:
	int arr[13][9];
	int unit[6][13][9];
	int temp[6][13][9];
// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CBjy_HexTriSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // Bjy_HexTriSView.cpp의 디버그 버전
inline CBjy_HexTriSDoc* CBjy_HexTriSView::GetDocument() const
   { return reinterpret_cast<CBjy_HexTriSDoc*>(m_pDocument); }
#endif

