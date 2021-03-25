#include "Stone.h"
#include "resource.h"
/*
void ShowStone(HDC hdc,Stone stone)
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
*/
/*
void ShowStone(HDC hdc,Stone stone,HINSTANCE hInstance)
{
	int textX,textY;
	char szBuffer[5];
	HDC hdcMemImag,hdcMemMask;
	HBITMAP hBitmapImag,hBitmapMask;
	int cxBitmap, cyBitmap ,d;
	BITMAP bitmap;

	hBitmapImag = LoadBitmap (hInstance,MAKEINTRESOURCE(stone.m_bBlack ? IDB_BLACK : IDB_WHITE)) ;
	GetObject (hBitmapImag, sizeof (BITMAP), &bitmap) ;
    cxBitmap = bitmap.bmWidth ;
    cyBitmap = bitmap.bmHeight ;

	hdcMemImag = CreateCompatibleDC (hdc) ;
	SelectObject (hdcMemImag, hBitmapImag) ;

	d = stone.m_rectStone.right - stone.m_rectStone.left;

	hBitmapMask = CreateBitmap (cxBitmap, cyBitmap, 1, 1, NULL) ;
	hdcMemMask = CreateCompatibleDC (hdc) ;
    SelectObject (hdcMemMask, hBitmapMask) ;

	SelectObject (hdcMemMask, GetStockObject (BLACK_BRUSH)) ;
	Rectangle (hdcMemMask, 0, 0, cxBitmap, cyBitmap) ;
	SelectObject (hdcMemMask, GetStockObject (WHITE_BRUSH)) ;
    Ellipse (hdcMemMask, 0, 0, cxBitmap, cyBitmap) ;

	BitBlt (hdcMemImag, 0, 0, cxBitmap, cyBitmap, hdcMemMask, 0, 0, SRCAND) ;

	if(stone.m_bShow)
	{
		SelectObject (hdcMemImag, hBitmapImag) ;
		SelectObject (hdcMemMask, hBitmapMask) ;

		StretchBlt(hdc, stone.m_rectStone.left, stone.m_rectStone.top, d, d, hdcMemMask, 0, 0, cxBitmap,cyBitmap,0x220326) ;
		StretchBlt(hdc, stone.m_rectStone.left, stone.m_rectStone.top, d, d, hdcMemImag, 0, 0, cxBitmap,cyBitmap,SRCPAINT) ;
		DeleteObject(hBitmapImag);
		DeleteObject(hBitmapMask);

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
*/
BOOL StoneOn(Stone stone[],int n,POINT point)
{
	int i;
	for(i=1;i<=n;i++)
	{
		if(PtInRect(&stone[i].m_rectStone,point) && stone[i].m_bShow)
			return TRUE;
	}
	return FALSE;	
}
