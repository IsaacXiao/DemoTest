#include "windows.h"
#include "CommCtrl.h"
#pragma comment(lib,"comctl32.lib")

void CreateMyTooltip (HWND hwnd,HINSTANCE ghThisInstance)
{
	INITCOMMONCONTROLSEX iccex; 
    HWND hwndTT; 
    TOOLINFO ti;
    unsigned int uid = 0;       
    LPTSTR lptstr;
	int id = GetWindowLong(hwnd,GWL_ID);
    RECT rect;                 
    iccex.dwICC = ICC_WIN95_CLASSES;
    iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    InitCommonControlsEx(&iccex);

	switch (id)
	{
	case 3://ID_SHOWCOODINATE
		 lptstr = TEXT("显示/隐藏坐标");
		 break;
	case 0://ID_PRE
		 lptstr = TEXT("上一手");
		 break;
	case 1://ID_NEXT
		 lptstr = TEXT("下一手");
		 break;
	case 2://ID_SHOWNUM
		 lptstr = TEXT("显示/隐藏手数");
		 break;
	case 4://ID_STONESTYLE
		 lptstr = TEXT("玻璃/水彩棋子");
		 break;
	}
    hwndTT = CreateWindowEx(WS_EX_TOPMOST,TOOLTIPS_CLASS,NULL,WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,		
			CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,hwnd,NULL,ghThisInstance,NULL);
    SetWindowPos(hwndTT,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    GetClientRect (hwnd, &rect);
		
    ti.cbSize = sizeof(TOOLINFO);
    ti.uFlags = TTF_SUBCLASS;
    ti.hwnd = hwnd;
    ti.hinst = ghThisInstance;
    ti.uId = uid;
    ti.lpszText = lptstr;

    ti.rect.left = rect.left;    
    ti.rect.top = rect.top;
    ti.rect.right = rect.right;
    ti.rect.bottom = rect.bottom;
  
    SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti);	
	SendMessage(hwndTT, TTM_SETDELAYTIME,TTDT_INITIAL,MAKELPARAM(100,0));
	SendMessage(hwndTT,TTM_SETTIPTEXTCOLOR,(WPARAM)RGB(0,0,255),0);
}

void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct,HDC hdc,BOOL m_bOver) 
{
	RECT rcClient;
	UINT state ;
	RECT rcFrame,rcFocus;
	HBRUSH hbrsh,hOldBrush;
	HPEN hpen,hpenFrame,hOldPen;

	hdc = lpDrawItemStruct->hDC;
	rcClient = lpDrawItemStruct->rcItem;
	state = lpDrawItemStruct->itemState;
	rcFrame = rcClient;
	rcFocus = rcClient;
		//背景色
	hbrsh = CreateSolidBrush( RGB( 255,255,255 ) );
	hOldBrush = SelectObject(hdc, hbrsh );

	hpen = CreatePen( PS_SOLID,1,( state&ODS_DISABLED ? RGB(255,255,255):RGB(0,60,116) ));
	hOldPen = SelectObject(hdc,hpen);
		//画按钮
	RoundRect(hdc,rcClient.left,rcClient.top,rcClient.right,rcClient.bottom,5,5);
	SelectObject(hdc, hOldPen);

	if ( m_bOver || ( state & ODS_SELECTED )  )//鼠标在按钮上面
	{
		hpenFrame = CreatePen( PS_SOLID,1,RGB(248,179,48) );
		hOldPen = SelectObject(hdc, hpenFrame );
		RoundRect(hdc,rcFrame.left,rcFrame.top,rcFrame.right,rcFrame.bottom,5,5 );
		DeleteObject(SelectObject(hdc, hOldPen ));
	}
}

void Triangle (HDC hdc, POINT pt[],BOOL m_bStart)
{
     if(m_bStart)
		SelectObject (hdc, CreateSolidBrush(RGB(128,128,128))) ;
	 else
		SelectObject (hdc, GetStockObject (BLACK_BRUSH)) ;
     Polygon (hdc, pt, 3) ;
     SelectObject (hdc, GetStockObject (WHITE_BRUSH)) ;
}	
