#include <windows.h>
#include "Stone.h"
#include "resource.h"

int WINAPI DllMain (HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved)
{
	return TRUE ;
}

_declspec(dllexport) void ShowStoneDraw(HDC hdc,Stone stone,HINSTANCE hInstance)
{
	int textX,textY;
	char szBuffer[5];
	HBRUSH hBrush;
	if(stone.m_bShow)
	{
		hBrush=(HBRUSH)GetStockObject(stone.m_bBlack ? BLACK_BRUSH : WHITE_BRUSH);
		SelectObject(hdc,hBrush);
		Ellipse(hdc,stone.m_rectStone.left,stone.m_rectStone.top,stone.m_rectStone.right,stone.m_rectStone.bottom);
		DeleteObject(hBrush);
		if(stone.m_bNumShow)
		{
			textX=stone.m_rectStone.left+9;
			textY=stone.m_rectStone.top+6;
			SetBkMode(hdc,TRANSPARENT);
			SetTextColor(hdc,RGB(255,0,0));
			sprintf(szBuffer,"%d",stone.CurrentNum);
			DrawText(hdc,szBuffer,strlen(szBuffer),&stone.m_rectStone,DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
	}
}


_declspec(dllexport) void ShowStoneGlass(HDC hdc,Stone stone,HINSTANCE hInstance)
{
	int textX,textY;
	char szBuffer[5];
	HDC hdcMemImag;
	HBITMAP hBitmapImag;
	int cxBitmap, cyBitmap ,d;
	BITMAP bitmap;
	
	hBitmapImag = LoadBitmap (hInstance,MAKEINTRESOURCE(stone.m_bBlack ? IDB_BLACK : IDB_WHITE)) ;
	GetObject (hBitmapImag, sizeof (BITMAP), &bitmap) ;
    cxBitmap = bitmap.bmWidth ;
    cyBitmap = bitmap.bmHeight ;
	
	hdcMemImag = CreateCompatibleDC (hdc) ;
	SelectObject (hdcMemImag, hBitmapImag) ;
	
	d = stone.m_rectStone.right - stone.m_rectStone.left;
	
	BeginPath(hdc);
	Ellipse(hdc,stone.m_rectStone.left,stone.m_rectStone.top,stone.m_rectStone.right,stone.m_rectStone.bottom);
	EndPath(hdc);
	SelectClipPath(hdc,RGN_COPY);
	
	if(stone.m_bShow)
	{
		StretchBlt(hdc, stone.m_rectStone.left, stone.m_rectStone.top, d, d,
			hdcMemImag, 0, 0, cxBitmap,cyBitmap,SRCCOPY) ;
		DeleteObject(hBitmapImag);
		
		if(stone.m_bNumShow)
		{
			textX=stone.m_rectStone.left+9;
			textY=stone.m_rectStone.top+6;
			SetBkMode(hdc,TRANSPARENT);
			SetTextColor(hdc,RGB(255,0,0));
			sprintf(szBuffer,"%d",stone.CurrentNum);
			DrawText(hdc,szBuffer,strlen(szBuffer),&stone.m_rectStone,DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
	}
}


