// Stone.cpp: implementation of the CStone class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "My.h"
#include "Stone.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStone::CStone()
{

}

CStone::~CStone()
{

}
CStone::CStone(BOOL red,int col,int row,LPCSTR name,int type,CPlate &plate)
{
	m_bShow=TRUE;
	m_bSelected=FALSE;
	m_bRed=red;
	m_nCol=col;
	m_Row=row;
	m_sName=name;
	m_nType=type;
	m_nR=23;
	CPoint pos=plate.GetPosition(col,row);
	m_rectStone=CRect(pos.x-m_nR,pos.y-m_nR,pos.x+m_nR,pos.y+m_nR);
}
void CStone::ShowStone(CDC *pDC)
{
	if(m_bShow)
	{
		CPen *pOldPen,penNormal(PS_SOLID,3,RGB(120,120,120));
		CBrush *pOldBrush,brushNormal,brushSelected;
		brushNormal.CreateSolidBrush(RGB(255,255,0));
		brushSelected.CreateSolidBrush(RGB(127,127,0));
		pOldPen=pDC->SelectObject(&penNormal);
		if(m_bSelected)
			pOldBrush=pDC->SelectObject(&brushSelected);
		else
			pOldBrush=pDC->SelectObject(&brushNormal);
		//显示棋子
		CRect r(m_rectStone);
		r.left++;
		r.top++;
		r.right--;
		r.bottom--;
		pDC->Ellipse(r);
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
		CFont *pOldFont,fontStone;
		fontStone.CreateFont(40,0,0,0,400,FALSE,FALSE,0,OEM_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"楷体");
		pOldFont=pDC->SelectObject(&fontStone);
		int tx=m_rectStone.left+6;
		int ty=m_rectStone.top+6;
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(m_bRed ? 255:0,0,0));
		pDC->TextOut(tx,ty,m_sName);
		pDC->SelectObject(pOldFont);
	}
}
void CStone::MoveTo(int col,int row,CPlate &plate)
{
	m_bSelected=FALSE;
	m_nCol=col;
	m_Row=row;
	CPoint pos=plate.GetPosition(col,row);
	m_rectStone=CRect(pos.x-m_nR,pos.y-m_nR,pos.x+m_nR,pos.y+m_nR);
}


BOOL CStone::Area()
{
	CPlate plate;
	CPoint CurrentPoint=GetRect().CenterPoint();
	//上下田心
	CRect AboveRect(plate.m_nLeft+3*plate.m_ndx-23,plate.m_nTop-23,
					plate.m_nLeft+5*plate.m_ndx+23,plate.m_nTop+2*plate.m_ndy+23);
	CRect UnderRect(plate.m_nLeft+3*plate.m_ndx-23,plate.m_nBottom-2*plate.m_ndy-23,
					plate.m_nLeft+5*plate.m_ndx+23,plate.m_nBottom+23);
	//上下河界
	CRect RedRect(plate.m_nLeft-23,plate.m_nTop-23,
				  plate.m_nRight+23,plate.m_nTop+4*plate.m_ndy+23);
	CRect BlackRect(plate.m_nLeft-23,plate.m_nTop+5*plate.m_ndy-23,
				  plate.m_nRight+23,plate.m_nBottom+23);
	switch(GetType())
	{
		case JIANG:
			if(m_bRed==TRUE)
			{
				if(AboveRect.PtInRect(CurrentPoint))
					return TRUE;
				else
					return FALSE;
			}
			else
			{
				if(UnderRect.PtInRect(CurrentPoint))
					return TRUE;
				else
					return FALSE;
			}
			break;
		case SHI:
			if(m_bRed==TRUE)
			{
				if(AboveRect.PtInRect(CurrentPoint))
					return TRUE;
				else
					return FALSE;
			}
			else
			{
				if(UnderRect.PtInRect(CurrentPoint))
					return TRUE;
				else
					return FALSE;
			}
			break;
		case XIANG:
			if(m_bRed==TRUE)
			{
				if(RedRect.PtInRect(CurrentPoint))
					return TRUE;
				else
					return FALSE;
			}
			else
			{
				if(BlackRect.PtInRect(CurrentPoint))
					return TRUE;
				else
					return FALSE;
			}
			break;
		case MA:

			break;
		case JU:

			break;
		case PAO:

			break;
		case BING:

			break;
		default:
			return TRUE;
	}
	return TRUE;
}
