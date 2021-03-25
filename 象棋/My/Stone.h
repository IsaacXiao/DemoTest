// Stone.h: interface for the CStone class.
//
//////////////////////////////////////////////////////////////////////

#include <afxwin.h>
#include "resource.h"
#include "plate.h"

#if !defined(AFX_STONE_H__AF2A4603_6FF6_4C60_8BA7_F9C419F9C0DC__INCLUDED_)
#define AFX_STONE_H__AF2A4603_6FF6_4C60_8BA7_F9C419F9C0DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BING 1
#define PAO 2
#define JU 3
#define MA 4
#define XIANG 5
#define SHI 6
#define JIANG 7

class CStone  
{
public:
	BOOL Area();
	CStone();
	CStone(BOOL red,int col,int row,LPCSTR name,int type,CPlate &plate);
	void ShowStone(CDC *pDC);
	void MoveTo(int col,int row,CPlate &plate);
	CRect GetRect() {return m_rectStone;}
	int GetType() {return m_nType;}
	BOOL BeKilled(int col,int row) {return m_bShow && m_nCol==col && m_Row==row;}
	BOOL MouseOnStone(CPoint point) {return m_rectStone.PtInRect(point) && m_bShow;}
	void KillIt() {m_bShow=FALSE;}
	void SelectStone() {m_bSelected = !m_bSelected;}
	virtual ~CStone();
	CRect m_rectStone;
	int m_nCol;
	int m_Row;
	BOOL m_bRed;
	BOOL m_bShow;
private:
	BOOL m_bSelected;
	CString m_sName;
	int m_nR;
	int m_nType;
};

#endif // !defined(AFX_STONE_H__AF2A4603_6FF6_4C60_8BA7_F9C419F9C0DC__INCLUDED_)
