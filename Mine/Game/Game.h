#include "Mine.h"
#include "NumShow.h"

// 游戏状态
#define GS_WAIT				0
#define GS_RUN				1

class GameDocument : public CDocument
{
public:
	HBITMAP g_hBmpMine   ;
	HBITMAP g_hBmpNumber ;
	HBITMAP g_hBmpFace   ;
	Mine    mines[9][9];
public:
	void SetTitle(LPCTSTR lpszTitle);
	BOOL WinGame();
	void LoseGame( int i, int j );
	void SafeSpread(int i, int j);
	void InitGame();
	GameDocument();
DECLARE_DYNCREATE( GameDocument ) 
};
IMPLEMENT_DYNCREATE(GameDocument, CDocument)

class GameView: public CView
{
	DECLARE_MESSAGE_MAP( )
	DECLARE_DYNCREATE(GameView)
public:
	UINT		m_uTimer;				// 定时器ID
	UINT		m_uGameState;			// 游戏状态是就绪还是已经开始
	NumShow		numShow2;				// 用来控制时间的数字框显示
	NumShow		numShow1;				// 用来控制雷个数的数字框显示
	BOOL		m_bClickMine;			// 方格是否被按下
	BOOL		m_bClickBtn;			// 笑脸是否被按下
	UINT		m_uSpendTime;			// 游戏开始击到目前所花费的时间
	UINT		m_uTimerRect[3];		// 时间的数字框区域坐标数组
	UINT		m_uNumRect[3];			// 雷个数的数字框区域坐标数组
	UINT		m_uBtnRect[3];			// 工具栏3个按钮的矩形X位置
	RECT		m_rcClient;				// 客户区矩形
	CRect		rectTool;				// 工具栏矩形
	CBrush		m_brsBG;				// 背景画刷对象
	UINT		m_uBtnState;			// 按钮状态
	bool		m_bOver;				// 游戏是否结束
	int nXPrePos;
	int nYPrePos;
	int nXCurPos;
	int nYCurPos;
	/*afx_msg void OnSize(UINT nType, int cx, int cy);*/
	afx_msg void OnTimer(UINT nIDEvent);
	void InitTimer();
	void DrawTimer(CDC* pDC);
	void DrawNumber(CDC* pDC);
	void DrawButton(CDC* pDC);
	GameView();
	GameDocument* GetDocument();
    virtual void OnDraw( CDC* pDC );
	afx_msg void OnNew();
	afx_msg void OnExit();
	afx_msg void OnAbout();
	/*afx_msg int OnCreate(LPCREATESTRUCT lpcs);*/
	void DrawMine(CDC *pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	/*afx_msg void OnMouseMove( UINT nFlags, CPoint point );*/
};
IMPLEMENT_DYNCREATE(GameView, CView)

class GameFrame: public CFrameWnd
{
	DECLARE_DYNCREATE(GameFrame)
	DECLARE_MESSAGE_MAP()
public:
// 	GameView *m_pwndView;
// 	GameFrame();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	/*afx_msg void OnSize( UINT nType, int cx, int cy );*/
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	CToolBar m_wndToolBar;
};
IMPLEMENT_DYNCREATE(GameFrame, CFrameWnd)

class GameApp: public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int  ExitInstance();
};
