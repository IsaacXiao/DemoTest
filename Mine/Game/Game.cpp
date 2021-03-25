// Game.cpp : Defines the entry point for the application.
//
#include "StdAfx.h"
#include "Game.h"
#include "resource.h"

//Document类**********************************************************

#define random(x) (rand()%x)

//工具栏的高度和宽度
#define TOOL_HEIGHT 34
#define TOOL_WIDTH  160

#define ID_TIMER_EVENT WM_USER + 1

void GameDocument::SetTitle(LPCTSTR lpszTitle)
{
	CDocument::SetTitle("扫雷");
}

BOOL GameDocument::WinGame()
{
	DWORD nX,nY;
	for( nX=0; nX<9; nX++ )
	{
		for( nY=0; nY<9; nY++ )
		{
			if ( !mines[nX][nY].m_bMine)
			{
				if ( mines[nX][nY].m_bShow )
				{
					continue;
				} 
				else
				{
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}

void GameDocument::LoseGame( int i, int j )
{	
	DWORD nX,nY;
	for( nX=0; nX<9; nX++ )
	{
		for( nY=0; nY<9; nY++ )
		{
			if ( mines[nX][nY].m_bMine )
			{
				mines[nX][nY].ShowRes();
			}
		}
	}
	mines[i][j].g_nShowBmp = 3;
}

/*
a[i-1,j-1]，a[i-1,j]，a[i-1,j+1] 
a[ i ,j-1],           a[ i ,j+1] 
a[i+1,j-1]，a[i+1,j]，a[i+1,j+1] 
*/

void GameDocument::SafeSpread(int i, int j)
{
	mines[i][j].m_bShow = TRUE;
	mines[i][j].ShowRes();
	mines[i][j].m_bTraveled = TRUE;

	//左上
	if(i&&j)
		if ( mines[i-1][j-1].m_bMine == FALSE )
		{
			mines[i-1][j-1].ShowRes();
			if( !mines[i-1][j-1].m_bTraveled && mines[i-1][j-1].m_bSafe )
				SafeSpread(i-1, j-1);
		}
	if(i)
	{
		//上方
		if(mines[i-1][j].m_bMine == FALSE)
		{
			mines[i-1][j].ShowRes();
			if( !mines[i-1][j].m_bTraveled && mines[i-1][j].m_bSafe)
				SafeSpread(i-1, j);
		}
		//右上
		if(j!=8)
			if (mines[i-1][j+1].m_bMine == FALSE)
			{
				mines[i-1][j+1].ShowRes();
				if( !mines[i-1][j+1].m_bTraveled && mines[i-1][j+1].m_bSafe )
					SafeSpread(i-1, j+1);
			}
	}
	if(j)
	{
		//左边
		if (mines[i][j-1].m_bMine == FALSE)
		{
			mines[i][j-1].ShowRes();
			if( !mines[i][j-1].m_bTraveled && mines[i][j-1].m_bSafe )
				SafeSpread(i, j-1);
		}
		//左下
		if(i!=8)
			if (mines[i+1][j-1].m_bMine == FALSE)
			{
				mines[i+1][j-1].ShowRes();
				if( !mines[i+1][j-1].m_bTraveled && mines[i+1][j-1].m_bSafe )
					SafeSpread(i+1, j-1);
			}
	}
	if(j!=8)
		//右边
		if (mines[i][j+1].m_bMine == FALSE)
		{
			mines[i][j+1].ShowRes();
			if( !mines[i][j+1].m_bTraveled && mines[i][j+1].m_bSafe )
				SafeSpread(i,j+1);
		}
	if(i!=8)
		//下方
		if (mines[i+1][j].m_bMine == FALSE)
		{
			mines[i+1][j].ShowRes();
			if( !mines[i+1][j].m_bTraveled && mines[i+1][j].m_bSafe )
				SafeSpread(i+1, j);
		}
	//右下
	if(i!=8&&j!=8)
		if (mines[i+1][j+1].m_bMine == FALSE)
		{
			mines[i+1][j+1].ShowRes();
			if( !mines[i+1][j+1].m_bTraveled && mines[i+1][j+1].m_bSafe )
				SafeSpread(i+1, j+1);
		}
}

//把哪个地方有雷，哪个地方有数字先确定好
void GameDocument::InitGame()
{
	//初始化
	DWORD nX,nY;
	for( nX=0; nX<9; nX++ )
	{
		for( nY=0; nY<9; nY++ )
		{
			mines[nX][nY].InitMine();
		}
	}	

	//10个随机位置有雷
	int i,j;
	for (i=0; i<9; i++)
	{
		j = random(9);
		//有雷的单元格该贴的图为5
		mines[i][j].g_nMineBmp = 5;
		mines[i][j].m_bMine = TRUE;
		
		if(i&&j)
			mines[i-1][j-1].num	+= 1;
		if(i)
		{
			mines[i-1][j].num	+= 1;
			if(j!=8)
				mines[i-1][j+1].num += 1;
		}
		if(j)
		{
			mines[i][j-1].num	+= 1;
			if(i!=8)
				mines[i+1][j-1].num += 1;
		}
		if(j!=8)
			mines[i][j+1].num	+= 1;
		if(i!=8)
			mines[i+1][j].num	+= 1;
		if(i!=8&&j!=8)
			mines[i+1][j+1].num += 1;
	}

	//第10颗雷
	i = random(9);
	j = random(9);
	mines[i][j].g_nMineBmp = 5;
	mines[i][j].m_bMine = TRUE;

	//有雷的单元格边上的4个点的数字算好
	if(i&&j)
		mines[i-1][j-1].num	+= 1;
	if(i)
	{
		mines[i-1][j].num	+= 1;
		if(j!=8)
			mines[i-1][j+1].num += 1;
	}
	if(j)
	{
		mines[i][j-1].num	+= 1;
		if(i!=8)
			mines[i+1][j-1].num += 1;
	}
	if(j!=8)
		mines[i][j+1].num	+= 1;
	if(i!=8)
		mines[i+1][j].num	+= 1;
	if(i!=8&&j!=8)
			mines[i+1][j+1].num += 1;

	//根据雷的数量确定无雷的单元格该贴哪个数字图
	for( nX=0; nX<9; nX++ )
	{
		for( nY=0; nY<9; nY++ )
		{
			if(!mines[nX][nY].m_bMine)
				mines[nX][nY].ShowNum();
				/*mines[nX][nY].g_nMineBmp = 15-mines[nX][nY].num;*/
		}
	}

	for( nX=0; nX<9; nX++ )
	{
		for( nY=0; nY<9; nY++ )
		{
			if ( mines[nX][nY].num == 0 )
			{
				mines[nX][nY].m_bSafe = TRUE;
			}
		}
	}
}

GameDocument::GameDocument()
{
	HINSTANCE g_hInst = AfxGetInstanceHandle();
	g_hBmpMine = LoadBitmap( g_hInst, 
		MAKEINTRESOURCE(IDB_MINE) );
	g_hBmpNumber = LoadBitmap( g_hInst, 
		MAKEINTRESOURCE(IDB_NUMBER) );
	g_hBmpFace = LoadBitmap( g_hInst, 
		MAKEINTRESOURCE(IDB_FACE) );

	InitGame();
}

//View类**********************************************************
	
BEGIN_MESSAGE_MAP(GameView, CView)
	ON_WM_PAINT()
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_ABOUT, OnAbout)
	ON_COMMAND(ID_NEW, OnNew)
	/*ON_WM_CREATE()*/
	ON_WM_LBUTTONDOWN( )
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

#define COLOR_GRAY RGB(192, 192, 192)

void GameView::OnTimer(UINT nIDEvent)
{
	++numShow2;
	Invalidate();
}

GameView::GameView():rectTool(0, 0, TOOL_WIDTH, TOOL_HEIGHT),numShow1( 0, 1, 0 ),numShow2( 0, 0, 0 )
{
	m_uTimer = 0;
	m_bClickMine = FALSE;
	m_bClickBtn = FALSE;
	m_bOver = false;
	m_brsBG.CreateSolidBrush(COLOR_GRAY);
	
	m_uBtnState = 4;	//按钮默认第4幅位图
	m_uGameState = GS_WAIT;
}

void GameView::OnNew()
{
	m_uGameState = GS_WAIT;

	if (m_uTimer)
	{
		KillTimer(ID_TIMER_EVENT);
		m_uTimer = 0;
	}

	m_bOver = false;
	GameDocument *pDoc = GetDocument();
	pDoc->InitGame();
	numShow1 = NumShow( 0, 1, 0 );
	numShow2 = NumShow( 0, 0, 0 );
	Invalidate();
}

void GameView::InitTimer()
{
	if (m_uTimer)
	{
		KillTimer(ID_TIMER_EVENT);
		m_uTimer = 0;
	}
	m_uSpendTime = 1;
	
	//启动定时器
	m_uTimer = SetTimer(ID_TIMER_EVENT, 1000, NULL);
	
	//改变游戏状态为运行状态
	m_uGameState = GS_RUN;
}

void GameView::OnLButtonUp( UINT nFlags, CPoint point )
{
	nXCurPos = ( point.x )/16;
	nYCurPos = ( point.y - TOOL_HEIGHT )/16;
	
	GameDocument *pDoc = GetDocument();

	GetClientRect(&m_rcClient);
	//若鼠标抬起来时离开了客户区
	if (!PtInRect( &m_rcClient, point ))
	{
		m_bClickBtn = FALSE;
		m_uBtnState = 4;

		if(m_bClickMine)
		{
			m_bClickMine = FALSE;
			pDoc->mines[nXPrePos][nYPrePos].g_nShowBmp = 0;	
		}	
		ReleaseCapture();
		Invalidate( );
		return;
	}
	else
	{
		m_uBtnState = 4;
		Invalidate();
	}
	ReleaseCapture();

	//如果在工具栏区域抬起鼠标
	if (PtInRect(&rectTool, point))
	{
		//笑脸按钮所在的区域
		CRect rcBtn( m_uBtnRect[0], (TOOL_HEIGHT-24)/2, m_uBtnRect[2], (TOOL_HEIGHT-24)/2+24);
		
		//在笑脸处按下去且在笑脸处抬起来的
		if (PtInRect( &rcBtn, point ) && m_bClickBtn)
		{
			//重新开局
			OnNew();
			m_bClickBtn = FALSE;
			return;
		}
	}

	if (m_bOver)
	{
		m_bClickMine = FALSE;
		m_bClickBtn = FALSE;
		return;
	}

	//鼠标抬起的地方在游戏区内
	if( nXCurPos < 9 && nYCurPos < 9 && m_bClickMine )
	{
		m_uBtnState = 4;
		//若鼠标抬起的位置与刚才鼠标按下的位置不相同,则贴图是默认图
		if ( nXCurPos!= nXPrePos || nYCurPos != nYPrePos)
		{
			pDoc->mines[nXPrePos][nYPrePos].g_nShowBmp = 0;
			Invalidate( );
			return;
		}
		else
		{
			if (m_uGameState == GS_WAIT) 
				InitTimer();

			//该单元格被显示
			pDoc->mines[nXCurPos][nYCurPos].m_bShow = TRUE;
			switch( pDoc->mines[nXCurPos][nYCurPos].g_nShowBmp )
			{
			case 15:
				m_bClickMine = FALSE;
				if (pDoc->mines[nXCurPos][nYCurPos].m_bShow)
				{
					//如果是雷则显示雷
					if (pDoc->mines[nXCurPos][nYCurPos].m_bMine)
					{
						pDoc->mines[nXCurPos][nYCurPos].g_nShowBmp = 3;
						/*AfxMessageBox("你踩到雷了！");*/
						m_bOver = true;

						KillTimer(ID_TIMER_EVENT);
						m_uTimer = 0;

						pDoc->LoseGame( nXCurPos, nYCurPos );

						m_uBtnState = 2;
					}
					//否则显示该显示的数字或者安全区
					else
					{
						//是安全区则递归遍历展开
						if (pDoc->mines[nXCurPos][nYCurPos].m_bSafe)
						{
							pDoc->SafeSpread(nXCurPos, nYCurPos);
						}
						//是数字则显示出来
						else
						{
							pDoc->mines[nXCurPos][nYCurPos].g_nShowBmp = 
							pDoc->mines[nXCurPos][nYCurPos].g_nMineBmp;
						}
						if ( pDoc->WinGame() )
						{
							KillTimer(ID_TIMER_EVENT);
							m_uTimer = 0;

							/*AfxMessageBox( "恭喜你赢了！");*/
							m_uBtnState = 1;
						}
					}
				}
				break;
			}
			Invalidate( );
		}
		return;
	}
}

void GameView::OnRButtonUp( UINT nFlags, CPoint point )
{
	if (m_bOver)
	{
		return;
	}

	nXCurPos = ( point.x )/16;
	nYCurPos = ( point.y - TOOL_HEIGHT )/16;
	
	GameDocument *pDoc = GetDocument();

	if( nXCurPos < 9 && nYCurPos < 9 )
	{
		switch( pDoc->mines[nXCurPos][nYCurPos].g_nShowBmp )
		{
		case 0:
			if ( numShow1[2]==11 && numShow1[1]==11 )
			{
				AfxMessageBox("最多排雷10个不能超过限制！");
				return;
			}	
			else
			{
				pDoc->mines[nXCurPos][nYCurPos].g_nShowBmp = 1;
				--numShow1;
			}
			break;
		case 1:
			pDoc->mines[nXCurPos][nYCurPos].g_nShowBmp = 2;
			++numShow1;
			break;
		case 2:
			pDoc->mines[nXCurPos][nYCurPos].g_nShowBmp = 0;
			break;
		}
		Invalidate( );
	}
}

void GameView::OnLButtonDown( UINT nFlags, CPoint point )
{
	SetCapture();

	//如果点击在工具栏区域
	if (PtInRect(&rectTool, point))
	{
		//笑脸按钮所在的区域
		CRect rcBtn( m_uBtnRect[0], (TOOL_HEIGHT-24)/2, m_uBtnRect[2], (TOOL_HEIGHT-24)/2+24);

		if (PtInRect( &rcBtn, point ))
		{
			//使笑脸看上去像被挤压按下去了一样，显示按钮第1幅位图
			m_uBtnState = 0;
			m_bClickBtn = TRUE;
		}
		else
		{
			m_uBtnState = 3;
		}
		Invalidate();
		return;
	}
	
	nXPrePos = ( point.x )/16;
	nYPrePos = ( point.y - TOOL_HEIGHT )/16;

	GameDocument *pDoc = GetDocument();

	if( nXPrePos < 9 && nYPrePos < 9 )
	{
		if (m_bOver)
		{
			return;
		}
		else
		{
			m_uBtnState = 3;
		}

		switch( pDoc->mines[nXPrePos][nYPrePos].g_nShowBmp )
		{
		case 0:
			pDoc->mines[nXPrePos][nYPrePos].g_nShowBmp = 15;
			m_bClickMine = TRUE;
			break;
		case 2:
			pDoc->mines[nXPrePos][nYPrePos].g_nShowBmp = 15;
			m_bClickMine = TRUE;
			break;
		}
		
		Invalidate( );
	}
}

GameDocument* GameView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(GameDocument)));
	return (GameDocument*)m_pDocument;
}

void GameView::DrawTimer(CDC* pDC)
{
	GameDocument * pDoc = GetDocument();
	
	CDC cdc;
	
	cdc.CreateCompatibleDC(pDC);
	CBitmap * pBmp = CBitmap::FromHandle(pDoc->g_hBmpNumber);
	CBitmap * pOld = cdc.SelectObject(pBmp);

	//数字为13*23大小的位图共有12幅
	pDC->StretchBlt(m_uTimerRect[0], (TOOL_HEIGHT-23)/2, 13, 23, 
		&cdc, 0, numShow2[0] * 23, 13, 23, SRCCOPY);
	pDC->StretchBlt(m_uTimerRect[1], (TOOL_HEIGHT-23)/2, 13, 23, 
		&cdc, 0, numShow2[1] * 23, 13, 23, SRCCOPY);
	pDC->StretchBlt(m_uTimerRect[2], (TOOL_HEIGHT-23)/2, 13, 23, 
		&cdc, 0, numShow2[2] * 23, 13, 23, SRCCOPY);
}

void GameView::DrawNumber(CDC* pDC)
{
	GameDocument * pDoc = GetDocument();
	
	CDC cdc;
	
	cdc.CreateCompatibleDC(pDC);
	CBitmap * pBmp = CBitmap::FromHandle(pDoc->g_hBmpNumber);
	CBitmap * pOld = cdc.SelectObject(pBmp);

	//数字为13*23大小的位图共有12幅
	pDC->StretchBlt(m_uNumRect[0], (TOOL_HEIGHT-23)/2, 13, 23, 
		&cdc, 0, numShow1[0] * 23, 13, 23, SRCCOPY);
	pDC->StretchBlt(m_uNumRect[1], (TOOL_HEIGHT-23)/2, 13, 23, 
		&cdc, 0, numShow1[1] * 23, 13, 23, SRCCOPY);
	pDC->StretchBlt(m_uNumRect[2], (TOOL_HEIGHT-23)/2, 13, 23, 
		&cdc, 0, numShow1[2] * 23, 13, 23, SRCCOPY);
}

void GameView::DrawButton(CDC* pDC)
{
	GameDocument * pDoc = GetDocument();

	CDC cdc;

	cdc.CreateCompatibleDC(pDC);
	CBitmap * pBmp = CBitmap::FromHandle(pDoc->g_hBmpFace);
	CBitmap * pOld = cdc.SelectObject(pBmp);

	pDC->StretchBlt(m_uBtnRect[0], (TOOL_HEIGHT-24)/2, 24, 24, 
		&cdc, 0, 24 * m_uBtnState, 24, 24, SRCCOPY);
}

void GameView::DrawMine( CDC* pDC )
{	
	HDC hDC = pDC->m_hDC;

	GameDocument *pDoc = GetDocument();
	
	HDC hBmpDC = CreateCompatibleDC( hDC );
	HBITMAP hOldBmp = (HBITMAP)
		SelectObject( hBmpDC, pDoc->g_hBmpMine );

	for( DWORD nX=0; nX<9; nX++ )
	{
		for( DWORD nY=0; nY<9; nY++ )
		{
			//每个雷宽和高占16像素
			int nSrcX = 0;
			int nSrcY = pDoc->mines[nX][nY].g_nShowBmp * 16;
			BitBlt( hDC, nX * 16, nY * 16 + TOOL_HEIGHT, 
				16, 16,	hBmpDC, 
				nSrcX, nSrcY, SRCCOPY );
		}
	}
	
	SelectObject( hBmpDC, hOldBmp );
	DeleteDC( hBmpDC );	
}

void GameView::OnExit()
{
	PostQuitMessage(0);
}

#include "AboutDlg.h"

void GameView::OnAbout()
{
	/*ShellAbout(this->m_hWnd, "扫雷", "cjohnXiao@gmail.com",NULL);*/
	CAboutDlg dlg;

	InitializeSkin(_T("XPCorona.ssk"));

	dlg.DoModal();
}

void GameView::OnDraw( CDC* pDC )
{
	GetClientRect(&m_rcClient);
	pDC->FillRect( &m_rcClient, &m_brsBG );

	m_uBtnRect[0] = m_rcClient.right / 2 - 12;			
	m_uBtnRect[1] = m_rcClient.right / 2 - 13;			
	m_uBtnRect[2] = m_rcClient.right / 2 + 12;	

	m_uNumRect[0] = m_rcClient.left + 9;				
	m_uNumRect[1] = m_uNumRect[0] + 13;				
	m_uNumRect[2] = m_uNumRect[1] + 13;	

	m_uTimerRect[0] = m_rcClient.right - 48;				
	m_uTimerRect[1] = m_uTimerRect[0] + 13;				
	m_uTimerRect[2] = m_uTimerRect[1] + 13;	

	DrawMine(pDC);
	DrawButton(pDC);
	DrawNumber(pDC);
	DrawTimer(pDC);
}

//Frame类**********************************************************

BEGIN_MESSAGE_MAP(GameFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()  
END_MESSAGE_MAP()

void GameFrame::OnGetMinMaxInfo(MINMAXINFO *lpMMI)  
{  
	CFrameWnd::OnGetMinMaxInfo(lpMMI);

// 	lpMMI->ptMinTrackSize.x = 234;
// 	lpMMI->ptMinTrackSize.y = 156;
}  

BOOL GameFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style&=~WS_MAXIMIZEBOX;  //禁用最大化按钮
	cs.style&=~WS_THICKFRAME;  //禁止调整窗口大小

	cs.cy = 234;
	cs.cx = 156;
	cs.y = ((::GetSystemMetrics(SM_CYSCREEN)) - cs.cy) / 2;
	cs.x = ((::GetSystemMetrics(SM_CXSCREEN)) - cs.cx) / 2;
	
	return CFrameWnd::PreCreateWindow(cs);
}

// GameFrame::GameFrame()
// {
// 	m_pwndView = NULL;
//     //View对象
//     m_pwndView = new GameView();
// }

int GameFrame::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

/*
    //创建View
    m_pwndView->Create( NULL, "View",
        WS_CHILD|WS_VISIBLE|WS_BORDER, 
        CFrameWnd::rectDefault,
        this, AFX_IDW_PANE_FIRST );
	
    SetActiveView( m_pwndView );
	
    ModifyStyleEx( WS_EX_CLIENTEDGE, 0 );

	SetIcon(AfxGetApp()->LoadIcon(MAKEINTRESOURCE(IDI_MAIN)),FALSE);
*/
	return 1;
}

//App类**********************************************************

GameApp theApp;

#include "SkinPPDLL\SkinPlusPlus.h"
#pragma comment(lib, "./SkinPPDLL/SkinPlusPlusDLL.lib")

BOOL GameApp::InitInstance()
{
/* 
	GameFrame* pWnd = new GameFrame();

    CCreateContext context;
    context.m_pNewViewClass = 
        RUNTIME_CLASS( GameView );
    //增加文档类的支持
    context.m_pCurrentDoc   =
        new GameDocument( );

    pWnd->Create( NULL, "扫雷", 
        WS_OVERLAPPEDWINDOW,
        CFrameWnd::rectDefault, NULL,
        MAKEINTRESOURCE(IDR_MAINFRM), 
		0, &context
		);	

	m_pMainWnd = pWnd;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

    //更新当前所有View
    pWnd->InitialUpdateFrame( NULL, TRUE );
*/
    CSingleDocTemplate * pTemp = NULL;
    pTemp = new CSingleDocTemplate( 
        IDR_MAINFRM,
        RUNTIME_CLASS( GameDocument ),
        RUNTIME_CLASS( GameFrame ),
        RUNTIME_CLASS( GameView ) 
		);
    //保存文档模板
    AddDocTemplate( pTemp );
	
    //新建文档
    OnFileNew( );
	
    //显示窗口
    m_pMainWnd->ShowWindow( SW_SHOW );
    m_pMainWnd->UpdateWindow( );

	InitializeSkin(_T("XPCorona.ssk"));

	return TRUE;
}

int GameApp::ExitInstance()
{
	ExitSkin();
	return CWinApp::ExitInstance();
}
