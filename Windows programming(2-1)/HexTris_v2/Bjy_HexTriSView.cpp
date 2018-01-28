
// Bjy_HexTriSView.cpp : CBjy_HexTriSView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Bjy_HexTriS.h"
#endif

#include "Bjy_HexTriSDoc.h"
#include "Bjy_HexTriSView.h"
#include "MainFrm.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBjy_HexTriSView

IMPLEMENT_DYNCREATE(CBjy_HexTriSView, CFormView)

	BEGIN_MESSAGE_MAP(CBjy_HexTriSView, CFormView)
		ON_WM_PAINT()
		ON_WM_TIMER()
		ON_COMMAND(ID_GAME_NEW, &CBjy_HexTriSView::OnGameNew)
	END_MESSAGE_MAP()

	// CBjy_HexTriSView 생성/소멸

	CBjy_HexTriSView::CBjy_HexTriSView()
		: CFormView(CBjy_HexTriSView::IDD)
		, m_iNowX(4)
		, m_iNowY(0)
		, p(0)
		, check(false)
		, m_iNowBlockDir(0)
		, m_iNowBlockShape(rand()%9)
		, m_iScore(0)
		, iRemoveLineCount(0)
		, str(_T(""))
		, pauseCheck(false)
		, rank(_T(""))
		, m_userName(_T(""))
	{
		// TODO: 여기에 생성 코드를 추가합니다.
		//pThread = ::AfxBeginThread (ThreadFunc, *ThreadInfo); 
	}

	CBjy_HexTriSView::~CBjy_HexTriSView()
	{
	}

	void CBjy_HexTriSView::DoDataExchange(CDataExchange* pDX)
	{
		CFormView::DoDataExchange(pDX);
	}

	BOOL CBjy_HexTriSView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs를 수정하여 여기에서
		//  Window 클래스 또는 스타일을 수정합니다.
		cs.cx = 400000;
		cs.cy = 1000;
		
 	return CFormView::PreCreateWindow(cs);
	}

	void CBjy_HexTriSView::OnInitialUpdate()
	{
		CFormView::OnInitialUpdate();
		GetParentFrame()->RecalcLayout();
		ResizeParentToFit();
		SetTimer(1,1000,NULL);

	}


	// CBjy_HexTriSView 진단

#ifdef _DEBUG
	void CBjy_HexTriSView::AssertValid() const
	{
		CFormView::AssertValid();
	}

	void CBjy_HexTriSView::Dump(CDumpContext& dc) const
	{
		CFormView::Dump(dc);
	}

	CBjy_HexTriSDoc* CBjy_HexTriSView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBjy_HexTriSDoc)));
		return (CBjy_HexTriSDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CBjy_HexTriSView 메시지 처리기


	void CBjy_HexTriSView::OnPaint()
	{
		srand((unsigned)time(NULL));
		CPaintDC dc(this); // device context for painting
		p.x = 210;
		p.y = 20;
		int a=p.y;
		int b=30;
		newUNIT(m_iNowBlockShape);
		CBrush WhiteBrush;
		WhiteBrush.CreateStockObject(NULL_BRUSH);
		CBrush NewBrush( RGB( 181, 123, 16 ) );
		CBrush NewBrushUnit( RGB( 172, 255, 0 ) );
		CBrush BrushBlock(RGB(245, 245, 37) );
		CBrush EndBlock(RGB(128, 128, 128) );
		dc.TextOutW(110,125,str);
		for(int i=0; i<13; i++){
			for(int j=0; j<9; j++){
				if(j==0||j==8||i==12) arr[i][j]=1;}
		}
		for(int i=0; i<13; i++){
			for(int j=0; j<9; j++){
				if(j%2==1)p.y = 20+a;
				else p.y = a;
				p.x+=b;

				if(arr[i][j]==1){
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrush = dc.SelectObject( &NewBrush );
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( pOldBrush );
				}
				else if(arr[i][j]==2){
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrush = dc.SelectObject( &BrushBlock );
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( pOldBrush );
				}
				else if(arr[i][j]==5){
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrush = dc.SelectObject( &EndBlock );
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( EndBlock );
				}
				else{
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrush = dc.SelectObject( &WhiteBrush );
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( EndBlock );
				}
				if(unit[m_iNowBlockDir][i][j]==1){
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrushUnit = dc.SelectObject( &NewBrushUnit );
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( pOldBrushUnit );
				}
				if(unit[m_iNowBlockDir][i][j]==2){
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrushUnit = dc.SelectObject( &NewBrushUnit );
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( pOldBrushUnit );
				}
				if(unit[m_iNowBlockDir][i][j]==3){
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrushUnit = dc.SelectObject( &NewBrushUnit );
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( pOldBrushUnit );
				}
				if(unit[m_iNowBlockDir][i][j]==4){
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrushUnit = dc.SelectObject( &NewBrushUnit );
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( pOldBrushUnit );
				}
				if(unit[m_iNowBlockDir][i][j]==5){
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrushUnit = dc.SelectObject( &NewBrushUnit );
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( pOldBrushUnit );
				}
				if(unit[m_iNowBlockDir][i][j]==6){
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrushUnit = dc.SelectObject( &NewBrushUnit );
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( pOldBrushUnit );
				}
				if(unit[m_iNowBlockDir][i][j]==7){
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrushUnit = dc.SelectObject( &NewBrushUnit);
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( pOldBrushUnit );
				}
				if(unit[m_iNowBlockDir][i][j]==8){
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrushUnit = dc.SelectObject( &NewBrushUnit );
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( pOldBrushUnit );
				}
				if(unit[m_iNowBlockDir][i][j]==9){
					POINT points[]={{p.x,p.y},{p.x+20,p.y},{p.x+30,p.y+20},{p.x+20,p.y+40},{p.x,p.y+40},{p.x-10,p.y+20},{p.x,p.y}};
					CBrush* pOldBrushUnit = dc.SelectObject( &NewBrushUnit );
					dc.Polygon(points,7);
					dc.EndPath();
					dc.SelectObject( pOldBrushUnit );
				}
			}
			a+=40;
			p.x=210;
		}
	}


	BOOL CBjy_HexTriSView::PreTranslateMessage(MSG* pMsg)
	{
		// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
		if (WM_KEYDOWN ==pMsg->message)
		{
			if(VK_LEFT == pMsg->wParam || 'a' == pMsg->wParam || 'A' == pMsg->wParam){
				if(canMove(m_iNowBlockDir, m_iNowX-1, m_iNowY)){
				
					m_iNowX-=1;
					newUNIT(m_iNowBlockShape);
				}
				Invalidate();
			}else  if(VK_RIGHT == pMsg->wParam || 'd' == pMsg->wParam || 'D' == pMsg->wParam){
				if(canMove(m_iNowBlockDir, m_iNowX+1, m_iNowY)){
					
					m_iNowX+=1;
					newUNIT(m_iNowBlockShape);
				}
				Invalidate();
			}else  if(VK_UP == pMsg->wParam || 'w' == pMsg->wParam || 'W' == pMsg->wParam){
				int temp3 = (m_iNowBlockDir+1)%6;
				if(canMove(temp3, m_iNowX, m_iNowY)){
					
					m_iNowBlockDir = temp3;
					newUNIT(m_iNowBlockShape);
				}
				Invalidate();
			}else  if(VK_DOWN == pMsg->wParam || 's' == pMsg->wParam || 'S' == pMsg->wParam){
				if(canMove(m_iNowBlockDir, m_iNowX, m_iNowY+1)){
				
					m_iNowY++;
				}
				Invalidate();
			}else if(VK_SPACE == pMsg->wParam){
				while(canMove(m_iNowBlockDir, m_iNowX, m_iNowY+1)){
					m_iNowY++;
				}
				Invalidate();
			}else if('p' == pMsg->wParam || 'P' == pMsg->wParam){
				if(!pauseCheck){
					KillTimer(1);
					CPaintDC dc(this);
					dc.TextOut(600, 100, _T("PAUSE"));
					pauseCheck=true;
				}
				else{
					SetTimer(1,1000,NULL);
					pauseCheck=false;
				}
			}if(pMsg->wParam == 'C' || pMsg->wParam == 'c' )        // 대/소문자 상관없이 CTRL+C를 위해
			{
				if( GetKeyState(VK_CONTROL))
				{
					KillTimer(1);

					if(IDYES == MessageBox(_T("한판 더 하시겠습니까"),_T("게임 종료.."),MB_YESNOCANCEL)){
						GameStart();
						Invalidate();
					}
					else{
						SetGameEND();
					}
				}
			}
		}
		return CFormView::PreTranslateMessage(pMsg);
	}




	void CBjy_HexTriSView::OnTimer(UINT_PTR nIDEvent)
	{

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		if(canMove(m_iNowBlockDir, m_iNowX, m_iNowY+1)){
			m_iNowY+=1;
			newUNIT(m_iNowBlockShape);
		}
		else{
			newUNIT(m_iNowBlockShape);
			stackBlock(m_iNowBlockDir);
			m_iNowY=0;
			m_iNowX=4;
			m_iNowBlockDir=0;
			m_iNowBlockShape = rand()%9;
		}
		iRemoveLineCount=0;

		iRemoveLineCount=LineNum();
		LineCheck();
		

		if(IsGameEnd()){
			KillTimer(1);

			if(IDYES == MessageBox(_T("한판 더 하시겠습니까"),_T(" HEX TETRIS"),MB_YESNOCANCEL)){
				GameStart();
				Invalidate();
			}
		}
		

		Invalidate();
		CFormView::OnTimer(nIDEvent);
	}
	
	void CBjy_HexTriSView::newUNIT(int val)
	{
		clearUNIT();
		switch(val){
		case 0:
			if(m_iNowX%2==0){
				unit[0][m_iNowY][m_iNowX]=unit[0][m_iNowY+1][m_iNowX]=unit[0][m_iNowY+2][m_iNowX]=unit[0][m_iNowY+3][m_iNowX]=1;
				unit[1][m_iNowY+1][m_iNowX+2]=unit[1][m_iNowY+1][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX]=unit[1][m_iNowY+2][m_iNowX-1]=1;
				unit[2][m_iNowY+3][m_iNowX+2]=unit[2][m_iNowY+2][m_iNowX+1]=unit[2][m_iNowY+2][m_iNowX]=unit[2][m_iNowY+1][m_iNowX-1]=1;
				unit[3][m_iNowY+1][m_iNowX]=unit[3][m_iNowY+2][m_iNowX]=unit[3][m_iNowY+3][m_iNowX]=unit[3][m_iNowY+4][m_iNowX]=1;
				unit[4][m_iNowY+1][m_iNowX+1]=unit[4][m_iNowY+2][m_iNowX]=unit[4][m_iNowY+2][m_iNowX-1]=unit[4][m_iNowY+3][m_iNowX-2]=1;
				unit[5][m_iNowY+2][m_iNowX+1]=unit[5][m_iNowY+2][m_iNowX]=unit[5][m_iNowY+1][m_iNowX-1]=unit[5][m_iNowY+1][m_iNowX-2]=1;
			}
			else{
				unit[0][m_iNowY][m_iNowX]=unit[0][m_iNowY+1][m_iNowX]=unit[0][m_iNowY+2][m_iNowX]=unit[0][m_iNowY+3][m_iNowX]=1;
				unit[1][m_iNowY+1][m_iNowX+2]=unit[1][m_iNowY+2][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX]=unit[1][m_iNowY+3][m_iNowX-1]=1;
				unit[2][m_iNowY+3][m_iNowX+2]=unit[2][m_iNowY+3][m_iNowX+1]=unit[2][m_iNowY+2][m_iNowX]=unit[2][m_iNowY+2][m_iNowX-1]=1;
				unit[3][m_iNowY+1][m_iNowX]=unit[3][m_iNowY+2][m_iNowX]=unit[3][m_iNowY+3][m_iNowX]=unit[3][m_iNowY+4][m_iNowX]=1;
				unit[4][m_iNowY+2][m_iNowX+1]=unit[4][m_iNowY+2][m_iNowX]=unit[4][m_iNowY+3][m_iNowX-1]=unit[4][m_iNowY+3][m_iNowX-2]=1;
				unit[5][m_iNowY+3][m_iNowX+1]=unit[5][m_iNowY+2][m_iNowX]=unit[5][m_iNowY+2][m_iNowX-1]=unit[5][m_iNowY+1][m_iNowX-2]=1;
			}
			break;
		case 1:
			if(m_iNowX%2==0){
				unit[0][m_iNowY][m_iNowX]=unit[0][m_iNowY+1][m_iNowX]=unit[0][m_iNowY+2][m_iNowX]=unit[0][m_iNowY+2][m_iNowX+1]=2;
				unit[1][m_iNowY+1][m_iNowX+2]=unit[1][m_iNowY+1][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX]=unit[1][m_iNowY+3][m_iNowX]=2;
				unit[2][m_iNowY+3][m_iNowX+2]=unit[2][m_iNowY+2][m_iNowX+1]=unit[2][m_iNowY+2][m_iNowX]=unit[2][m_iNowY+2][m_iNowX-1]=2;
				unit[3][m_iNowY+4][m_iNowX]=unit[3][m_iNowY+3][m_iNowX]=unit[3][m_iNowY+2][m_iNowX]=unit[3][m_iNowY+1][m_iNowX-1]=2;
				unit[4][m_iNowY+3][m_iNowX-2]=unit[4][m_iNowY+2][m_iNowX-1]=unit[4][m_iNowY+2][m_iNowX]=unit[4][m_iNowY+1][m_iNowX]=2;
				unit[5][m_iNowY+1][m_iNowX-2]=unit[5][m_iNowY+1][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX]=unit[5][m_iNowY+1][m_iNowX+1]=2;
			}
			else{
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX]=unit[0][m_iNowY+3][m_iNowX+1]=2;
				unit[1][m_iNowY+1][m_iNowX+2]=unit[1][m_iNowY+2][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX]=unit[1][m_iNowY+3][m_iNowX  ]=2;
				unit[2][m_iNowY+3][m_iNowX+2]=unit[2][m_iNowY+3][m_iNowX+1]=unit[2][m_iNowY+2][m_iNowX]=unit[2][m_iNowY+3][m_iNowX-1]=2;
				unit[3][m_iNowY+4][m_iNowX  ]=unit[3][m_iNowY+3][m_iNowX  ]=unit[3][m_iNowY+2][m_iNowX]=unit[3][m_iNowY+2][m_iNowX-1]=2;
				unit[4][m_iNowY+3][m_iNowX-2]=unit[4][m_iNowY+3][m_iNowX-1]=unit[4][m_iNowY+2][m_iNowX]=unit[4][m_iNowY+1][m_iNowX  ]=2;
				unit[5][m_iNowY+1][m_iNowX-2]=unit[5][m_iNowY+2][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX]=unit[5][m_iNowY+2][m_iNowX+1]=2;
			}
			break;
		case 2:
			if(m_iNowX%2==0){
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX+1]=unit[0][m_iNowY+2][m_iNowX+1]=3;
				unit[1][m_iNowY  ][m_iNowX+2]=unit[1][m_iNowY  ][m_iNowX+1]=unit[1][m_iNowY+1][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX  ]=3;
				unit[2][m_iNowY+1][m_iNowX+3]=unit[2][m_iNowY+1][m_iNowX+2]=unit[2][m_iNowY+1][m_iNowX+1]=unit[2][m_iNowY+1][m_iNowX  ]=3;
				unit[3][m_iNowY+3][m_iNowX+2]=unit[3][m_iNowY+2][m_iNowX+2]=unit[3][m_iNowY+1][m_iNowX+1]=unit[3][m_iNowY  ][m_iNowX+1]=3;
				unit[4][m_iNowY+3][m_iNowX  ]=unit[4][m_iNowY+2][m_iNowX+1]=unit[4][m_iNowY+1][m_iNowX+1]=unit[4][m_iNowY+1][m_iNowX+2]=3;
				unit[5][m_iNowY+1][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX  ]=unit[5][m_iNowY+1][m_iNowX+1]=unit[5][m_iNowY+2][m_iNowX+2]=3;
			}
			else{
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX+1]=unit[0][m_iNowY+3][m_iNowX+1]=3;
				unit[1][m_iNowY  ][m_iNowX+2]=unit[1][m_iNowY+1][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX  ]=3;
				unit[2][m_iNowY+2][m_iNowX+3]=unit[2][m_iNowY+1][m_iNowX+2]=unit[2][m_iNowY+2][m_iNowX+1]=unit[2][m_iNowY+1][m_iNowX  ]=3;
				unit[3][m_iNowY+3][m_iNowX+2]=unit[3][m_iNowY+2][m_iNowX+2]=unit[3][m_iNowY+2][m_iNowX+1]=unit[3][m_iNowY+1][m_iNowX+1]=3;
				unit[4][m_iNowY+3][m_iNowX  ]=unit[4][m_iNowY+3][m_iNowX+1]=unit[4][m_iNowY+2][m_iNowX+1]=unit[4][m_iNowY+1][m_iNowX+2]=3;
				unit[5][m_iNowY+2][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX  ]=unit[5][m_iNowY+2][m_iNowX+1]=unit[5][m_iNowY+2][m_iNowX+2]=3;
			}
			break;
		case 3:
			if(m_iNowX%2==0){
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX-1]=4;
				unit[1][m_iNowY+1][m_iNowX+2]=unit[1][m_iNowY+1][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX  ]=unit[1][m_iNowY+1][m_iNowX  ]=4;
				unit[2][m_iNowY+3][m_iNowX+2]=unit[2][m_iNowY+2][m_iNowX+1]=unit[2][m_iNowY+2][m_iNowX  ]=unit[2][m_iNowY+1][m_iNowX+1]=4;
				unit[3][m_iNowY+4][m_iNowX  ]=unit[3][m_iNowY+3][m_iNowX  ]=unit[3][m_iNowY+2][m_iNowX  ]=unit[3][m_iNowY+2][m_iNowX+1]=4;
				unit[4][m_iNowY+3][m_iNowX-2]=unit[4][m_iNowY+3][m_iNowX  ]=unit[4][m_iNowY+2][m_iNowX  ]=unit[4][m_iNowY+2][m_iNowX-1]=4;
				unit[5][m_iNowY+1][m_iNowX-2]=unit[5][m_iNowY+2][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX  ]=unit[5][m_iNowY+1][m_iNowX-1]=4;
			}
			else{
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX-1]=4;
				unit[1][m_iNowY+1][m_iNowX+2]=unit[1][m_iNowY+2][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX  ]=unit[1][m_iNowY+1][m_iNowX  ]=4;
				unit[2][m_iNowY+3][m_iNowX+2]=unit[2][m_iNowY+3][m_iNowX+1]=unit[2][m_iNowY+2][m_iNowX  ]=unit[2][m_iNowY+2][m_iNowX+1]=4;
				unit[3][m_iNowY+4][m_iNowX  ]=unit[3][m_iNowY+3][m_iNowX  ]=unit[3][m_iNowY+2][m_iNowX  ]=unit[3][m_iNowY+3][m_iNowX+1]=4;
				unit[4][m_iNowY+3][m_iNowX-2]=unit[4][m_iNowY+3][m_iNowX  ]=unit[4][m_iNowY+2][m_iNowX  ]=unit[4][m_iNowY+3][m_iNowX-1]=4;
				unit[5][m_iNowY+1][m_iNowX-2]=unit[5][m_iNowY+2][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX  ]=unit[5][m_iNowY+3][m_iNowX-1]=4;
			}
			break;
		case 4:
			if(m_iNowX%2==0){
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX+1]=5;
				unit[1][m_iNowY+1][m_iNowX+2]=unit[1][m_iNowY+1][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX  ]=unit[1][m_iNowY+2][m_iNowX+1]=5;
				unit[2][m_iNowY+3][m_iNowX+2]=unit[2][m_iNowY+2][m_iNowX+1]=unit[2][m_iNowY+2][m_iNowX  ]=unit[2][m_iNowY+3][m_iNowX  ]=5;
				unit[3][m_iNowY+4][m_iNowX  ]=unit[3][m_iNowY+3][m_iNowX  ]=unit[3][m_iNowY+2][m_iNowX  ]=unit[3][m_iNowY+2][m_iNowX-1]=5;
				unit[4][m_iNowY+3][m_iNowX-2]=unit[4][m_iNowY+2][m_iNowX-1]=unit[4][m_iNowY+2][m_iNowX  ]=unit[4][m_iNowY+1][m_iNowX-1]=5;
				unit[5][m_iNowY+1][m_iNowX-2]=unit[5][m_iNowY+1][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX  ]=unit[5][m_iNowY+1][m_iNowX  ]=5;
			}
			else{
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX+1]=5;
				unit[1][m_iNowY+1][m_iNowX+2]=unit[1][m_iNowY+2][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX  ]=unit[1][m_iNowY+3][m_iNowX+1]=5;
				unit[2][m_iNowY+3][m_iNowX+2]=unit[2][m_iNowY+3][m_iNowX+1]=unit[2][m_iNowY+2][m_iNowX  ]=unit[2][m_iNowY+3][m_iNowX  ]=5;
				unit[3][m_iNowY+4][m_iNowX  ]=unit[3][m_iNowY+3][m_iNowX  ]=unit[3][m_iNowY+2][m_iNowX  ]=unit[3][m_iNowY+3][m_iNowX-1]=5;
				unit[4][m_iNowY+3][m_iNowX-2]=unit[4][m_iNowY+3][m_iNowX-1]=unit[4][m_iNowY+2][m_iNowX  ]=unit[4][m_iNowY+2][m_iNowX-1]=5;
				unit[5][m_iNowY+1][m_iNowX-2]=unit[5][m_iNowY+2][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX  ]=unit[5][m_iNowY+1][m_iNowX  ]=5;
			}
			break;
		case 5:
			if(m_iNowX%2==0){
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX-1]=unit[0][m_iNowY+1][m_iNowX-2]=6;
				unit[1][m_iNowY+1][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX  ]=unit[1][m_iNowY+1][m_iNowX-1]=unit[1][m_iNowY  ][m_iNowX-1]=6;
				unit[2][m_iNowY+3][m_iNowX  ]=unit[2][m_iNowY+2][m_iNowX-1]=unit[2][m_iNowY+1][m_iNowX-1]=unit[2][m_iNowY+1][m_iNowX  ]=6;
				unit[3][m_iNowY+3][m_iNowX-2]=unit[3][m_iNowY+2][m_iNowX-2]=unit[3][m_iNowY+1][m_iNowX-1]=unit[3][m_iNowY+2][m_iNowX  ]=6;
				unit[4][m_iNowY+1][m_iNowX-3]=unit[4][m_iNowY+1][m_iNowX-2]=unit[4][m_iNowY+1][m_iNowX-1]=unit[4][m_iNowY+2][m_iNowX-1]=6;
				unit[5][m_iNowY  ][m_iNowX-2]=unit[5][m_iNowY  ][m_iNowX-1]=unit[5][m_iNowY+1][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX-2]=6;
			}
			else{
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX-1]=unit[0][m_iNowY+1][m_iNowX-2]=6;
				unit[1][m_iNowY+2][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX  ]=unit[1][m_iNowY+2][m_iNowX-1]=unit[1][m_iNowY+1][m_iNowX-1]=6;
				unit[2][m_iNowY+3][m_iNowX  ]=unit[2][m_iNowY+3][m_iNowX-1]=unit[2][m_iNowY+2][m_iNowX-1]=unit[2][m_iNowY+1][m_iNowX  ]=6;
				unit[3][m_iNowY+3][m_iNowX-2]=unit[3][m_iNowY+2][m_iNowX-2]=unit[3][m_iNowY+2][m_iNowX-1]=unit[3][m_iNowY+2][m_iNowX  ]=6;
				unit[4][m_iNowY+2][m_iNowX-3]=unit[4][m_iNowY+1][m_iNowX-2]=unit[4][m_iNowY+2][m_iNowX-1]=unit[4][m_iNowY+3][m_iNowX-1]=6;
				unit[5][m_iNowY  ][m_iNowX-2]=unit[5][m_iNowY+1][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX-2]=6;
			}
			break;
		case 6:
			if(m_iNowX%2==0){
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY  ][m_iNowX-1]=unit[0][m_iNowY  ][m_iNowX+1]=7;
				unit[1][m_iNowY  ][m_iNowX+1]=unit[1][m_iNowY+1][m_iNowX  ]=unit[1][m_iNowY  ][m_iNowX  ]=unit[1][m_iNowY+1][m_iNowX+1]=7;
				unit[2][m_iNowY+1][m_iNowX+1]=unit[2][m_iNowY+1][m_iNowX  ]=unit[2][m_iNowY  ][m_iNowX+1]=unit[2][m_iNowY+2][m_iNowX  ]=7;
				unit[3][m_iNowY+2][m_iNowX  ]=unit[3][m_iNowY+1][m_iNowX  ]=unit[3][m_iNowY+1][m_iNowX+1]=unit[3][m_iNowY+1][m_iNowX-1]=7;
				unit[4][m_iNowY+1][m_iNowX-1]=unit[4][m_iNowY+1][m_iNowX  ]=unit[4][m_iNowY+2][m_iNowX  ]=unit[4][m_iNowY  ][m_iNowX-1]=7;
				unit[5][m_iNowY  ][m_iNowX-1]=unit[5][m_iNowY+1][m_iNowX  ]=unit[5][m_iNowY+1][m_iNowX-1]=unit[5][m_iNowY  ][m_iNowX  ]=7;
			}
			else{
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX-1]=unit[0][m_iNowY+1][m_iNowX+1]=7;
				unit[1][m_iNowY+1][m_iNowX+1]=unit[1][m_iNowY+1][m_iNowX  ]=unit[1][m_iNowY  ][m_iNowX  ]=unit[1][m_iNowY+2][m_iNowX+1]=7;
				unit[2][m_iNowY+2][m_iNowX+1]=unit[2][m_iNowY+1][m_iNowX  ]=unit[2][m_iNowY+1][m_iNowX+1]=unit[2][m_iNowY+2][m_iNowX  ]=7;
				unit[3][m_iNowY+2][m_iNowX  ]=unit[3][m_iNowY+1][m_iNowX  ]=unit[3][m_iNowY+2][m_iNowX+1]=unit[3][m_iNowY+2][m_iNowX-1]=7;
				unit[4][m_iNowY+2][m_iNowX-1]=unit[4][m_iNowY+1][m_iNowX  ]=unit[4][m_iNowY+2][m_iNowX  ]=unit[4][m_iNowY+1][m_iNowX-1]=7;
				unit[5][m_iNowY+1][m_iNowX-1]=unit[5][m_iNowY+1][m_iNowX  ]=unit[5][m_iNowY+2][m_iNowX-1]=unit[5][m_iNowY  ][m_iNowX  ]=7;
			}
			break;
		case 7:
			if(m_iNowX%2==0){
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX-1]=unit[0][m_iNowY+2][m_iNowX-1]=8;
				unit[1][m_iNowY+1][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX  ]=unit[1][m_iNowY+1][m_iNowX-1]=unit[1][m_iNowY+2][m_iNowX-2]=8;
				unit[2][m_iNowY+3][m_iNowX  ]=unit[2][m_iNowY+2][m_iNowX-1]=unit[2][m_iNowY+1][m_iNowX-1]=unit[2][m_iNowY+1][m_iNowX-2]=8;
				unit[3][m_iNowY+3][m_iNowX-2]=unit[3][m_iNowY+2][m_iNowX-2]=unit[3][m_iNowY+1][m_iNowX-1]=unit[3][m_iNowY  ][m_iNowX-1]=8;
				unit[4][m_iNowY+1][m_iNowX-3]=unit[4][m_iNowY+1][m_iNowX-2]=unit[4][m_iNowY+1][m_iNowX-1]=unit[4][m_iNowY+1][m_iNowX  ]=8;
				unit[5][m_iNowY  ][m_iNowX-2]=unit[5][m_iNowY  ][m_iNowX-1]=unit[5][m_iNowY+1][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX  ]=8;
			}
			else{
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX-1]=unit[0][m_iNowY+3][m_iNowX-1]=8;
				unit[1][m_iNowY+2][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX  ]=unit[1][m_iNowY+2][m_iNowX-1]=unit[1][m_iNowY+2][m_iNowX-2]=8;
				unit[2][m_iNowY+3][m_iNowX  ]=unit[2][m_iNowY+3][m_iNowX-1]=unit[2][m_iNowY+2][m_iNowX-1]=unit[2][m_iNowY+1][m_iNowX-2]=8;
				unit[3][m_iNowY+3][m_iNowX-2]=unit[3][m_iNowY+2][m_iNowX-2]=unit[3][m_iNowY+2][m_iNowX-1]=unit[3][m_iNowY+1][m_iNowX-1]=8;
				unit[4][m_iNowY+2][m_iNowX-3]=unit[4][m_iNowY+1][m_iNowX-2]=unit[4][m_iNowY+2][m_iNowX-1]=unit[4][m_iNowY+1][m_iNowX  ]=8;
				unit[5][m_iNowY  ][m_iNowX-2]=unit[5][m_iNowY+1][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX  ]=8;
			}
			break;
		case 8:
			if(m_iNowX%2==0){
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX-1]=9;
				unit[1][m_iNowY+1][m_iNowX+2]=unit[1][m_iNowY+1][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX  ]=unit[1][m_iNowY+1][m_iNowX-1]=9;
				unit[2][m_iNowY+3][m_iNowX+2]=unit[2][m_iNowY+2][m_iNowX+1]=unit[2][m_iNowY+2][m_iNowX  ]=unit[2][m_iNowY+1][m_iNowX  ]=9;
				unit[3][m_iNowY+4][m_iNowX  ]=unit[3][m_iNowY+3][m_iNowX  ]=unit[3][m_iNowY+2][m_iNowX  ]=unit[3][m_iNowY+1][m_iNowX+1]=9;
				unit[4][m_iNowY+3][m_iNowX-2]=unit[4][m_iNowY+2][m_iNowX-1]=unit[4][m_iNowY+2][m_iNowX  ]=unit[4][m_iNowY+2][m_iNowX+1]=9;
				unit[5][m_iNowY+1][m_iNowX-2]=unit[5][m_iNowY+1][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX  ]=unit[5][m_iNowY+3][m_iNowX  ]=9;
			}
			else{
				unit[0][m_iNowY  ][m_iNowX  ]=unit[0][m_iNowY+1][m_iNowX  ]=unit[0][m_iNowY+2][m_iNowX  ]=unit[0][m_iNowY+3][m_iNowX-1]=9;
				unit[1][m_iNowY+1][m_iNowX+2]=unit[1][m_iNowY+2][m_iNowX+1]=unit[1][m_iNowY+2][m_iNowX  ]=unit[1][m_iNowY+2][m_iNowX-1]=9;
				unit[2][m_iNowY+3][m_iNowX+2]=unit[2][m_iNowY+3][m_iNowX+1]=unit[2][m_iNowY+2][m_iNowX  ]=unit[2][m_iNowY+1][m_iNowX  ]=9;
				unit[3][m_iNowY+4][m_iNowX  ]=unit[3][m_iNowY+3][m_iNowX  ]=unit[3][m_iNowY+2][m_iNowX  ]=unit[3][m_iNowY+2][m_iNowX+1]=9;
				unit[4][m_iNowY+3][m_iNowX-2]=unit[4][m_iNowY+3][m_iNowX-1]=unit[4][m_iNowY+2][m_iNowX  ]=unit[4][m_iNowY+3][m_iNowX+1]=9;
				unit[5][m_iNowY+1][m_iNowX-2]=unit[5][m_iNowY+2][m_iNowX-1]=unit[5][m_iNowY+2][m_iNowX  ]=unit[5][m_iNowY+3][m_iNowX  ]=9;
			}
			break;
		default:
			break;
		}
	}
	
	void CBjy_HexTriSView::tempUNIT(int val, int x, int y)
	{
		clearUNIT();
		switch(val){
		case 0:
			if(m_iNowX%2==0){
				temp[0][y][x]=temp[0][y+1][x]=temp[0][y+2][x]=temp[0][y+3][x]=1;
				temp[1][y+1][x+2]=temp[1][y+1][x+1]=temp[1][y+2][x]=temp[1][y+2][x-1]=1;
				temp[2][y+3][x+2]=temp[2][y+2][x+1]=temp[2][y+2][x]=temp[2][y+1][x-1]=1;
				temp[3][y+1][x]=temp[3][y+2][x]=temp[3][y+3][x]=temp[3][y+4][x]=1;
				temp[4][y+1][x+1]=temp[4][y+2][x]=temp[4][y+2][x-1]=temp[4][y+3][x-2]=1;
				temp[5][y+2][x+1]=temp[5][y+2][x]=temp[5][y+1][x-1]=temp[5][y+1][x-2]=1;
			}
			else{
				temp[0][y][x]=temp[0][y+1][x]=temp[0][y+2][x]=temp[0][y+3][x]=1;
				temp[1][y+1][x+2]=temp[1][y+2][x+1]=temp[1][y+2][x]=temp[1][y+3][x-1]=1;
				temp[2][y+3][x+2]=temp[2][y+3][x+1]=temp[2][y+2][x]=temp[2][y+2][x-1]=1;
				temp[3][y+1][x]=temp[3][y+2][x]=temp[3][y+3][x]=temp[3][y+4][x]=1;
				temp[4][y+2][x+1]=temp[4][y+2][x]=temp[4][y+3][x-1]=temp[4][y+3][x-2]=1;
				temp[5][y+3][x+1]=temp[5][y+2][x]=temp[5][y+2][x-1]=temp[5][y+1][x-2]=1;
			}
			break;
		case 1: 
			if(m_iNowX%2==0){
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+2][x]=temp[0][y+2][x+1]=1;
				temp[1][y+1][x+2]=temp[1][y+1][x+1]=temp[1][y+2][x]=temp[1][y+3][x  ]=1;
				temp[2][y+3][x+2]=temp[2][y+2][x+1]=temp[2][y+2][x]=temp[2][y+2][x-1]=1;
				temp[3][y+4][x  ]=temp[3][y+3][x  ]=temp[3][y+2][x]=temp[3][y+1][x-1]=1;
				temp[4][y+3][x-2]=temp[4][y+2][x-1]=temp[4][y+2][x]=temp[4][y+1][x  ]=1;
				temp[5][y+1][x-2]=temp[5][y+1][x-1]=temp[5][y+2][x]=temp[5][y+1][x+1]=1;
			}
			else{
				temp[0][y][x]=temp[0][y+1][x]=temp[0][y+2][x]=temp[0][y+3][x+1]=1;
				temp[1][y+1][x+2]=temp[1][y+2][x+1]=temp[1][y+2][x]=temp[1][y+3][x]=1;
				temp[2][y+3][x+2]=temp[2][y+3][x+1]=temp[2][y+2][x]=temp[2][y+3][x-1]=1;
				temp[3][y+4][x]=temp[3][y+3][x]=temp[3][y+2][x]=temp[3][y+2][x-1]=1;
				temp[4][y+3][x-2]=temp[4][y+3][x-1]=temp[4][y+2][x]=temp[4][y+1][x]=1;
				temp[5][y+1][x-2]=temp[5][y+2][x-1]=temp[5][y+2][x]=temp[5][y+2][x+1]=1;
			}
			break;
		case 2:
			if(m_iNowX%2==0){
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+1][x+1]=temp[0][y+2][x+1]=1;
				temp[1][y  ][x+2]=temp[1][y  ][x+1]=temp[1][y+1][x+1]=temp[1][y+2][x  ]=1;
				temp[2][y+1][x+3]=temp[2][y+1][x+2]=temp[2][y+1][x+1]=temp[2][y+1][x  ]=1;
				temp[3][y+3][x+2]=temp[3][y+2][x+2]=temp[3][y+1][x+1]=temp[3][y  ][x+1]=1;
				temp[4][y+3][x  ]=temp[4][y+2][x+1]=temp[4][y+1][x+1]=temp[4][y+1][x+2]=1;
				temp[5][y+1][x-1]=temp[5][y+2][x  ]=temp[5][y+1][x+1]=temp[5][y+2][x+2]=1;
			}
			else{
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+2][x+1]=temp[0][y+3][x+1]=1;
				temp[1][y  ][x+2]=temp[1][y+1][x+1]=temp[1][y+2][x+1]=temp[1][y+2][x  ]=1;
				temp[2][y+2][x+3]=temp[2][y+1][x+2]=temp[2][y+2][x+1]=temp[2][y+1][x  ]=1;
				temp[3][y+3][x+2]=temp[3][y+2][x+2]=temp[3][y+2][x+1]=temp[3][y+1][x+1]=1;
				temp[4][y+3][x  ]=temp[4][y+3][x+1]=temp[4][y+2][x+1]=temp[4][y+1][x+2]=1;
				temp[5][y+2][x-1]=temp[5][y+2][x  ]=temp[5][y+2][x+1]=temp[5][y+2][x+2]=1;
			}
			break;
		case 3:
			if(m_iNowX%2==0){
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+2][x  ]=temp[0][y+1][x-1]=1;
				temp[1][y+1][x+2]=temp[1][y+1][x+1]=temp[1][y+2][x  ]=temp[1][y+1][x  ]=1;
				temp[2][y+3][x+2]=temp[2][y+2][x+1]=temp[2][y+2][x  ]=temp[2][y+1][x+1]=1;
				temp[3][y+4][x  ]=temp[3][y+3][x  ]=temp[3][y+2][x  ]=temp[3][y+2][x+1]=1;
				temp[4][y+3][x-2]=temp[4][y+3][x  ]=temp[4][y+2][x  ]=temp[4][y+2][x-1]=1;
				temp[5][y+1][x-2]=temp[5][y+2][x-1]=temp[5][y+2][x  ]=temp[5][y+1][x-1]=1;
			}
			else{
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+2][x  ]=temp[0][y+2][x-1]=1;
				temp[1][y+1][x+2]=temp[1][y+2][x+1]=temp[1][y+2][x  ]=temp[1][y+1][x  ]=1;
				temp[2][y+3][x+2]=temp[2][y+3][x+1]=temp[2][y+2][x  ]=temp[2][y+2][x+1]=1;
				temp[3][y+4][x  ]=temp[3][y+3][x  ]=temp[3][y+2][x  ]=temp[3][y+3][x+1]=1;
				temp[4][y+3][x-2]=temp[4][y+3][x  ]=temp[4][y+2][x  ]=temp[4][y+3][x-1]=1;
				temp[5][y+1][x-2]=temp[5][y+2][x-1]=temp[5][y+2][x  ]=temp[5][y+3][x-1]=1;
			}
			break;
		case 4:
			if(m_iNowX%2==0){
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+2][x  ]=temp[0][y+1][x+1]=1;
				temp[1][y+1][x+2]=temp[1][y+1][x+1]=temp[1][y+2][x  ]=temp[1][y+2][x+1]=1;
				temp[2][y+3][x+2]=temp[2][y+2][x+1]=temp[2][y+2][x  ]=temp[2][y+3][x  ]=1;
				temp[3][y+4][x  ]=temp[3][y+3][x  ]=temp[3][y+2][x  ]=temp[3][y+2][x-1]=1;
				temp[4][y+3][x-2]=temp[4][y+2][x-1]=temp[4][y+2][x  ]=temp[4][y+1][x-1]=1;
				temp[5][y+1][x-2]=temp[5][y+1][x-1]=temp[5][y+2][x  ]=temp[5][y+1][x  ]=1;
			}
			else{
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+2][x  ]=temp[0][y+2][x+1]=1;
				temp[1][y+1][x+2]=temp[1][y+2][x+1]=temp[1][y+2][x  ]=temp[1][y+3][x+1]=1;
				temp[2][y+3][x+2]=temp[2][y+3][x+1]=temp[2][y+2][x  ]=temp[2][y+3][x  ]=1;
				temp[3][y+4][x  ]=temp[3][y+3][x  ]=temp[3][y+2][x  ]=temp[3][y+3][x-1]=1;
				temp[4][y+3][x-2]=temp[4][y+3][x-1]=temp[4][y+2][x  ]=temp[4][y+2][x-1]=1;
				temp[5][y+1][x-2]=temp[5][y+2][x-1]=temp[5][y+2][x  ]=temp[5][y+1][x  ]=1;
			}
			break;
		case 5:
			if(m_iNowX%2==0){
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+1][x-1]=temp[0][y+1][x-2]=1;
				temp[1][y+1][x+1]=temp[1][y+2][x  ]=temp[1][y+1][x-1]=temp[1][y  ][x-1]=1;
				temp[2][y+3][x  ]=temp[2][y+2][x-1]=temp[2][y+1][x-1]=temp[2][y+1][x  ]=1;
				temp[3][y+3][x-2]=temp[3][y+2][x-2]=temp[3][y+1][x-1]=temp[3][y+2][x  ]=1;
				temp[4][y+1][x-3]=temp[4][y+1][x-2]=temp[4][y+1][x-1]=temp[4][y+2][x-1]=1;
				temp[5][y  ][x-2]=temp[5][y  ][x-1]=temp[5][y+1][x-1]=temp[5][y+2][x-2]=1;
			}
			else{
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+2][x-1]=temp[0][y+1][x-2]=1;
				temp[1][y+2][x+1]=temp[1][y+2][x  ]=temp[1][y+2][x-1]=temp[1][y+1][x-1]=1;
				temp[2][y+3][x  ]=temp[2][y+3][x-1]=temp[2][y+2][x-1]=temp[2][y+1][x  ]=1;
				temp[3][y+3][x-2]=temp[3][y+2][x-2]=temp[3][y+2][x-1]=temp[3][y+2][x  ]=1;
				temp[4][y+2][x-3]=temp[4][y+1][x-2]=temp[4][y+2][x-1]=temp[4][y+3][x-1]=1;
				temp[5][y  ][x-2]=temp[5][y+1][x-1]=temp[5][y+2][x-1]=temp[5][y+2][x-2]=1;
			}
			break;
		case 6:
			if(m_iNowX%2==0){
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y  ][x-1]=temp[0][y  ][x+1]=1;
				temp[1][y  ][x+1]=temp[1][y+1][x  ]=temp[1][y  ][x  ]=temp[1][y+1][x+1]=1;
				temp[2][y+1][x+1]=temp[2][y+1][x  ]=temp[2][y  ][x+1]=temp[2][y+2][x  ]=1;
				temp[3][y+2][x  ]=temp[3][y+1][x  ]=temp[3][y+1][x+1]=temp[3][y+1][x-1]=1;
				temp[4][y+1][x-1]=temp[4][y+1][x  ]=temp[4][y+2][x  ]=temp[4][y  ][x-1]=1;
				temp[5][y  ][x-1]=temp[5][y+1][x  ]=temp[5][y+1][x-1]=temp[5][y  ][x  ]=1;
			}
			else{
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+1][x-1]=temp[0][y+1][x+1]=1;
				temp[1][y+1][x+1]=temp[1][y+1][x  ]=temp[1][y  ][x  ]=temp[1][y+2][x+1]=1;
				temp[2][y+2][x+1]=temp[2][y+1][x  ]=temp[2][y+1][x+1]=temp[2][y+2][x  ]=1;
				temp[3][y+2][x  ]=temp[3][y+1][x  ]=temp[3][y+2][x+1]=temp[3][y+2][x-1]=1;
				temp[4][y+2][x-1]=temp[4][y+1][x  ]=temp[4][y+2][x  ]=temp[4][y+1][x-1]=1;
				temp[5][y+1][x-1]=temp[5][y+1][x  ]=temp[5][y+2][x-1]=temp[5][y  ][x  ]=1;
			}
			break;
		case 7:
			if(m_iNowX%2==0){
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+1][x-1]=temp[0][y+2][x-1]=1;
				temp[1][y+1][x+1]=temp[1][y+2][x  ]=temp[1][y+1][x-1]=temp[1][y+2][x-2]=1;
				temp[2][y+3][x  ]=temp[2][y+2][x-1]=temp[2][y+1][x-1]=temp[2][y+1][x-2]=1;
				temp[3][y+3][x-2]=temp[3][y+2][x-2]=temp[3][y+1][x-1]=temp[3][y  ][x-1]=1;
				temp[4][y+1][x-3]=temp[4][y+1][x-2]=temp[4][y+1][x-1]=temp[4][y+1][x  ]=1;
				temp[5][y  ][x-2]=temp[5][y  ][x-1]=temp[5][y+1][x-1]=temp[5][y+2][x  ]=1;
			}
			else{
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+2][x-1]=temp[0][y+3][x-1]=1;
				temp[1][y+2][x+1]=temp[1][y+2][x  ]=temp[1][y+2][x-1]=temp[1][y+2][x-2]=1;
				temp[2][y+3][x  ]=temp[2][y+3][x-1]=temp[2][y+2][x-1]=temp[2][y+1][x-2]=1;
				temp[3][y+3][x-2]=temp[3][y+2][x-2]=temp[3][y+2][x-1]=temp[3][y+1][x-1]=1;
				temp[4][y+2][x-3]=temp[4][y+1][x-2]=temp[4][y+2][x-1]=temp[4][y+1][x  ]=1;
				temp[5][y  ][x-2]=temp[5][y+1][x-1]=temp[5][y+2][x-1]=temp[5][y+2][x  ]=1;
			}
			break;
		case 8:
			if(m_iNowX%2==0){
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+2][x  ]=temp[0][y+2][x-1]=1;
				temp[1][y+1][x+2]=temp[1][y+1][x+1]=temp[1][y+2][x  ]=temp[1][y+1][x-1]=1;
				temp[2][y+3][x+2]=temp[2][y+2][x+1]=temp[2][y+2][x  ]=temp[2][y+1][x  ]=1;
				temp[3][y+4][x  ]=temp[3][y+3][x  ]=temp[3][y+2][x  ]=temp[3][y+1][x+1]=1;
				temp[4][y+3][x-2]=temp[4][y+2][x-1]=temp[4][y+2][x  ]=temp[4][y+2][x+1]=1;
				temp[5][y+1][x-2]=temp[5][y+1][x-1]=temp[5][y+2][x  ]=temp[5][y+3][x  ]=1;
			}
			else{
				temp[0][y  ][x  ]=temp[0][y+1][x  ]=temp[0][y+2][x  ]=temp[0][y+3][x-1]=1;
				temp[1][y+1][x+2]=temp[1][y+2][x+1]=temp[1][y+2][x  ]=temp[1][y+2][x-1]=1;
				temp[2][y+3][x+2]=temp[2][y+3][x+1]=temp[2][y+2][x  ]=temp[2][y+1][x  ]=1;
				temp[3][y+4][x  ]=temp[3][y+3][x  ]=temp[3][y+2][x  ]=temp[3][y+2][x+1]=1;
				temp[4][y+3][x-2]=temp[4][y+3][x-1]=temp[4][y+2][x  ]=temp[4][y+3][x+1]=1;
				temp[5][y+1][x-2]=temp[5][y+2][x-1]=temp[5][y+2][x  ]=temp[5][y+3][x  ]=1;
			}
			break;
		default:
			break;
		}
	}
	void CBjy_HexTriSView::clearUNIT(void)
	{
		for(int i=0; i<6; i++){
			for(int j=0; j<13; j++){
				for(int k=0; k<9; k++){
					unit[i][j][k]=0;
				}
			}
		}
	}


	BOOL CBjy_HexTriSView::canMove(int dir, int x, int y)
	{
		if(pauseCheck) return false;
		tempUNIT(m_iNowBlockShape, x, y);
		for(int i=0; i<13; i++){
			for(int j=0; j<9; j++){
				if((arr[i][j]==1 || arr[i][j]==2) && temp[dir][i][j]==1){
					tempClear();
					return false;
				}
			}
		}
		tempClear();
		return true;
	}



	void CBjy_HexTriSView::tempClear(void)
	{
		for(int i=0; i<6; i++){
			for(int j=0; j<13; j++){
				for(int k=0; k<9; k++){
					temp[i][j][k]=0;
				}
			}
		}
	}




	void CBjy_HexTriSView::LineCheck(void)
	{
		int a = 0;
		for(int i=11; i>=0; i--){
			for(int j=1; j<8; j++){
				if(arr[i][j]==1 || arr[i][j]==2 ) a++;
			}

			if(a==7){
				
				for(int d=i; d>0; d--){
					for(int j=1; j<8; j++){
						arr[d][j]=arr[d-1][j];
					}
				}
			}
			a=0;
		}
	}


	bool CBjy_HexTriSView::IsGameEnd(void)
	{
		for(int i=1; i<8; i++){
			if(arr[0][i]==1 || arr[0][i]==2){
				return true;
			}
		}
		return false;
	}

	
	
	void CBjy_HexTriSView::GameStart(void)
	{
		for(int i=0; i<12; i++){
			for(int j=1; j<8; j++){
				arr[i][j]=0;
			}
		}
		SetTimer(1,1000,NULL); // 1번 타이머를 1000mS(즉,1초)마다 동작
		srand( (unsigned)time( NULL ) ); 
		m_iNowBlockShape = rand()%7;
		m_iScore=0;
		m_iNowBlockDir = 0;
		m_iNowX = 4;
		m_iNowY = 0;
	}

	void CBjy_HexTriSView::stackBlock(int val)
	{
		
		for(int i=0; i<13; i++){
			for(int j=0; j<9; j++){
				if( unit[val][i][j]==1 || unit[val][i][j]==2 || unit[val][i][j]==3 || unit[val][i][j]==4 || unit[val][i][j]==5 || unit[val][i][j]==6 || unit[val][i][j]==7 || unit[val][i][j]==8 || unit[val][i][j]==9){
					arr[i][j]=2;
				}
			}
		}
	
	}



	void CBjy_HexTriSView::SetGameEND(void)
	{
		for(int i=0; i<12; i++){
			for(int j=1; j<8; j++){
				if(arr[i][j]==1 || arr[i][j]==2 ) arr[i][j]=5;
			}
		}
		Invalidate();
	}


	int CBjy_HexTriSView::LineNum(void)
	{
		int a = 0;
		int num=0;
		for(int i=11; i>=0; i--){
			for(int j=1; j<8; j++){
				if(arr[i][j]==1 || arr[i][j]==2 ) a++;
			}

			if(a==7){
				num++;
			}
			a=0;
		}
		return num;
	}


	void CBjy_HexTriSView::OnGameNew()
	{
		GameStart();
		CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
		pFrm->MoveWindow(0, 0, 100, 200);
		Invalidate();
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
	}
