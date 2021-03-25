// plate.cpp: implementation of the CPlate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "My.h"
#include "plate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlate::CPlate()
{
	m_ndx=50;
	m_ndy=45;
	m_nLeft=198;
	m_nTop=30;
	m_nRight=m_nLeft+m_ndx*8;
	m_nBottom=m_nTop+m_ndy*9;
}

void CPlate::ShowPlate(CDC *pDC)
{
	CPen penRed2(PS_SOLID,2,RGB(255,0,0));
	CPen *pOldPen=pDC->SelectObject(&penRed2);

	for(int i=0;i<10;i++)
	{
		pDC->MoveTo(m_nLeft,m_nTop+i*m_ndy);
		pDC->LineTo(m_nRight,m_nTop+i*m_ndy);
	}
	for(i=0;i<9;i++)
	{
		if(i==0 || i==8)
		{
			pDC->MoveTo(m_nLeft+i*m_ndx,m_nTop);
			pDC->LineTo(m_nLeft+i*m_ndx,m_nBottom);
		}
		else
		{
			pDC->MoveTo(m_nLeft+i*m_ndx,m_nTop);
			pDC->LineTo(m_nLeft+i*m_ndx,m_nTop+4*m_ndy);
			pDC->MoveTo(m_nLeft+i*m_ndx,m_nTop+5*m_ndy);
			pDC->LineTo(m_nLeft+i*m_ndx,m_nBottom);
		}
	}
	pDC->SelectObject(pOldPen);
	CPen penRed1(PS_SOLID,1,RGB(255,0,0));
	pOldPen=pDC->SelectObject(&penRed1);
	pDC->MoveTo(m_nLeft+3*m_ndx,m_nTop);
	pDC->LineTo(m_nLeft+5*m_ndx,m_nTop+2*m_ndy);
	pDC->MoveTo(m_nLeft+3*m_ndx,m_nTop+2*m_ndy);
	pDC->LineTo(m_nLeft+5*m_ndx,m_nTop);
	pDC->MoveTo(m_nLeft+3*m_ndx,m_nBottom);
	pDC->LineTo(m_nLeft+5*m_ndx,m_nBottom-2*m_ndy);
	pDC->MoveTo(m_nLeft+3*m_ndx,m_nBottom-2*m_ndy);
	pDC->LineTo(m_nLeft+5*m_ndx,m_nBottom);
	pDC->SelectObject(pOldPen);
	DrawConer(pDC,2,1,0);
	DrawConer(pDC,2,7,0);
	DrawConer(pDC,3,0,1);
	DrawConer(pDC,3,2,0);
	DrawConer(pDC,3,4,0);
	DrawConer(pDC,3,6,0);
	DrawConer(pDC,3,8,2);
	DrawConer(pDC,7,1,0);
	DrawConer(pDC,7,7,0);
	DrawConer(pDC,6,0,1);
	DrawConer(pDC,6,2,0);
	DrawConer(pDC,6,4,0);
	DrawConer(pDC,6,6,0);
	DrawConer(pDC,6,8,2);
//	CPen penRed3(PS_SOLID,2,RGB(255,255,0));
//	pOldPen=pDC->SelectObject(&penRed3);
//	CRect RedRect(m_nLeft-23,m_nTop+5*m_ndy-23,
//				  m_nRight+23,m_nBottom+23);
//	pDC->Rectangle(&RedRect);
}

void CPlate::DrawConer(CDC *pDC,int row,int col,int type)
{
	CPen penRed1(PS_SOLID,1,RGB(255,0,0));
	CPen *pOldPen=pDC->SelectObject(&penRed1);
	if(type==0 || type==1)
	{
		pDC->MoveTo(m_nLeft+col*m_ndx+3,m_nTop+row*m_ndy-10);
		pDC->LineTo(m_nLeft+col*m_ndx+3,m_nTop+row*m_ndy-3);
		pDC->LineTo(m_nLeft+col*m_ndx+10,m_nTop+row*m_ndy-3);
		pDC->MoveTo(m_nLeft+col*m_ndx+3,m_nTop+row*m_ndy+10);
		pDC->LineTo(m_nLeft+col*m_ndx+3,m_nTop+row*m_ndy+3);
		pDC->LineTo(m_nLeft+col*m_ndx+10,m_nTop+row*m_ndy+3);
	}
	if(type==0 || type==2)
	{
		pDC->MoveTo(m_nLeft+col*m_ndx-3,m_nTop+row*m_ndy-10);
		pDC->LineTo(m_nLeft+col*m_ndx-3,m_nTop+row*m_ndy-3);
		pDC->LineTo(m_nLeft+col*m_ndx-10,m_nTop+row*m_ndy-3);
		pDC->MoveTo(m_nLeft+col*m_ndx-3,m_nTop+row*m_ndy+10);
		pDC->LineTo(m_nLeft+col*m_ndx-3,m_nTop+row*m_ndy+3);
		pDC->LineTo(m_nLeft+col*m_ndx-10,m_nTop+row*m_ndy+3);
	}
	pDC->SelectObject(pOldPen);
}

CPoint CPlate::GetPosition(int col,int row)
{
	CPoint point;
	point.x=m_nLeft+col*m_ndx;
	point.y=m_nTop+row*m_ndy;
	return point;
}
 
CPlate::~CPlate()
{

}
