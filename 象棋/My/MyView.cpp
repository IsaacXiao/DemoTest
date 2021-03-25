// MyView.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "My.h"

#include "MyDoc.h"
#include "MyView.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView construction/destruction

CMyView::CMyView()
{
	// TODO: add construction code here
	InitGame();
}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView drawing

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	m_Plate.ShowPlate(pDC);
	for(int i=0;i<32;i++)
		m_StoneList[i].ShowStone(pDC);
	ShowInfo(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView printing

BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers

BOOL CMyView::MoveTo(int col, int row)
{
	StoneRectPre=m_StoneList[m_nWhichStone].GetRect();
	m_PreRow=m_StoneList[m_nWhichStone].m_Row;
	m_PreCol=m_StoneList[m_nWhichStone].m_nCol;
	InvalidateRect(m_StoneList[m_nWhichStone].GetRect());
	m_StoneList[m_nWhichStone].MoveTo(col,row,m_Plate);
	if(m_StoneList[m_nWhichStone].Area() && StoneMoveRules())
	{
		InvalidateRect(m_StoneList[m_nWhichStone].GetRect());
		m_bSelectOne=FALSE;
		int i=KillEnemy(col,row,m_bRedTurn);
		if(i>=0)
		{
			m_StoneList[i].KillIt();
			if(m_StoneList[i].GetType()==JIANG)
			{
				if(m_bRedTurn)
					MessageBox("红方胜!");
				else
					MessageBox("黑方胜!");
				InitGame();
				Invalidate();
				return TRUE;
			}
		}
		if(FaceToFace())
		{
			if(m_bRedTurn)
				MessageBox("黑方胜!");
			else
				MessageBox("红方胜!");
			InitGame();
			Invalidate();
			return TRUE;			
		}
		InvalidateRect(m_rectInfo);
		return !m_bRedTurn;
	}
	else
	{
		if(!m_StoneList[m_nWhichStone].Area())
			Area();
		else
			Rules();
		m_StoneList[m_nWhichStone].m_rectStone=StoneRectPre;
		m_StoneList[m_nWhichStone].m_Row=m_PreRow;
		m_StoneList[m_nWhichStone].m_nCol=m_PreCol;
		m_StoneList[m_nWhichStone].SelectStone();
		InvalidateRect(m_StoneList[m_nWhichStone].m_rectStone);
		return m_bRedTurn;
	}
}
void CMyView::InitGame()
{
	m_bRedTurn=TRUE;
	m_bSelectOne=FALSE;
	m_rectInfo=CRect(315,480,515,550);
	m_StoneList[0]=CStone(TRUE,0,0,"车",3,m_Plate);
	m_StoneList[1]=CStone(TRUE,1,0,"马",4,m_Plate);
	m_StoneList[2]=CStone(TRUE,2,0,"相",5,m_Plate);
	m_StoneList[3]=CStone(TRUE,3,0,"仕",6,m_Plate);
	m_StoneList[4]=CStone(TRUE,4,0,"帅",7,m_Plate);
	m_StoneList[5]=CStone(TRUE,5,0,"仕",6,m_Plate);
	m_StoneList[6]=CStone(TRUE,6,0,"相",5,m_Plate);
	m_StoneList[7]=CStone(TRUE,7,0,"马",4,m_Plate);
	m_StoneList[8]=CStone(TRUE,8,0,"车",3,m_Plate);
	m_StoneList[9]=CStone(TRUE,1,2,"炮",2,m_Plate);
	m_StoneList[10]=CStone(TRUE,7,2,"炮",2,m_Plate);
	m_StoneList[11]=CStone(TRUE,0,3,"兵",1,m_Plate);
	m_StoneList[12]=CStone(TRUE,2,3,"兵",1,m_Plate);
	m_StoneList[13]=CStone(TRUE,4,3,"兵",1,m_Plate);
	m_StoneList[14]=CStone(TRUE,6,3,"兵",1,m_Plate);
	m_StoneList[15]=CStone(TRUE,8,3,"兵",1,m_Plate);
	m_StoneList[16]=CStone(FALSE,0,9,"车",3,m_Plate);
	m_StoneList[17]=CStone(FALSE,1,9,"马",4,m_Plate);
	m_StoneList[18]=CStone(FALSE,2,9,"象",5,m_Plate);
	m_StoneList[19]=CStone(FALSE,3,9,"士",6,m_Plate);
	m_StoneList[20]=CStone(FALSE,4,9,"将",7,m_Plate);
	m_StoneList[21]=CStone(FALSE,5,9,"士",6,m_Plate);
	m_StoneList[22]=CStone(FALSE,6,9,"象",5,m_Plate);
	m_StoneList[23]=CStone(FALSE,7,9,"马",4,m_Plate);
	m_StoneList[24]=CStone(FALSE,8,9,"车",3,m_Plate);
	m_StoneList[25]=CStone(FALSE,1,7,"炮",2,m_Plate);
	m_StoneList[26]=CStone(FALSE,7,7,"炮",2,m_Plate);
	m_StoneList[27]=CStone(FALSE,0,6,"卒",1,m_Plate);
	m_StoneList[28]=CStone(FALSE,2,6,"卒",1,m_Plate);
	m_StoneList[29]=CStone(FALSE,4,6,"卒",1,m_Plate);
	m_StoneList[30]=CStone(FALSE,6,6,"卒",1,m_Plate);
	m_StoneList[31]=CStone(FALSE,8,6,"卒",1,m_Plate);
}
void CMyView::ShowInfo(CDC *pDC)
{
	CFont *pOldFont,fontInfo;
	fontInfo.CreateFont(50,0,0,0,400,FALSE,FALSE,0,OEM_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"楷体");
	pOldFont=pDC->SelectObject(&fontInfo);
	pDC->SetTextColor(RGB(m_bRedTurn ? 255:0,0,0));
	pDC->TextOut(m_rectInfo.left,m_rectInfo.top,m_bRedTurn ? "红方行棋":"黑方行棋");
	pDC->SelectObject(pOldFont);
}
BOOL CMyView::KillSelfStone(int col,int row,BOOL red)
{
	int from=red ? 0:16;
	for(int i=from;i<from+16;i++)
	{
		if(m_StoneList[i].BeKilled(col,row))
			return TRUE;
	}
	return FALSE;
}
int CMyView::KillEnemy(int col,int row,BOOL red)
{
	int from=red ? 16:0;
	int i;
	for(i=from;i<from+16;i++)
	{
		if(m_StoneList[i].BeKilled(col,row))
			return i;
	}
	return -i;
}
void CMyView::MoveStone(CPoint point)
{
	if(m_StoneList[m_nWhichStone].MouseOnStone(point))
	{
		m_StoneList[m_nWhichStone].SelectStone();
		m_bSelectOne=FALSE;
		InvalidateRect(m_StoneList[m_nWhichStone].GetRect(),FALSE);
	}
	else
		Go(point);
}
void CMyView::SelectStone(CPoint point)
{
	int nwhich=m_bRedTurn ? 0:16;
	for(int i=nwhich;i<nwhich+16;i++)
		if(m_StoneList[i].MouseOnStone(point))
		{
			m_StoneList[i].SelectStone();
			InvalidateRect(m_StoneList[i].GetRect(),FALSE);
			m_nWhichStone=i;
			m_bSelectOne=TRUE;
			break;
		}
}
void CMyView::Go(CPoint point)
{
	for(int col=0;col<9;col++)
		for(int row=0;row<10;row++)
		{
			CPoint p=m_Plate.GetPosition(col,row);
			r=CRect(p.x-23,p.y-23,p.x+23,p.y+23);
			if(r.PtInRect(point))
			{
				if(KillSelfStone(col,row,m_bRedTurn))
					MessageBox("您竟然想吃自己人!?");
				else
					m_bRedTurn=MoveTo(col,row);
			}
		}
}

void CMyView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bSelectOne)
		MoveStone(point);
	else
		SelectStone(point);
	CView::OnLButtonDown(nFlags, point);
}
void CMyView::Area()
{
	MessageBox("超出棋子行走范围!");
}

void CMyView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect RectPlate(m_Plate.m_nLeft,m_Plate.m_nTop,m_Plate.m_nRight,m_Plate.m_nBottom);
	if(RectPlate.PtInRect(point))
	{
		::SetCursor(::LoadCursor(NULL,IDC_CROSS));
	}
	else
		::SetCursor(::LoadCursor(NULL,IDC_ARROW));
	CView::OnMouseMove(nFlags, point);
}

BOOL CMyView::StoneMoveRules()
{
	CPoint CurPoint=m_StoneList[m_nWhichStone].GetRect().CenterPoint();
	CPoint PrePoint=StoneRectPre.CenterPoint();
	CPlate plate;
	CRect RedRect(plate.m_nLeft-23,plate.m_nTop-23,
				  plate.m_nRight+23,plate.m_nTop+4*plate.m_ndy+23);
	CRect BlackRect(plate.m_nLeft-23,plate.m_nTop+5*plate.m_ndy-23,
				  plate.m_nRight+23,plate.m_nBottom+23);
	CSize offset(CurPoint-PrePoint);
	int i,j,sign;
	int count=0;
	switch(m_StoneList[m_nWhichStone].GetType())
	{
		case JIANG:
			if( (abs(offset.cx)==50 && abs(offset.cy)==0) ||
				(abs(offset.cx)==0 && abs(offset.cy)==45) )
				return TRUE;
			else
				return FALSE;
		case SHI:
			if(abs(offset.cx)==50 && abs(offset.cy)==45)
				return TRUE;
			else
				return FALSE;
		case XIANG:
			if(abs(offset.cx)==100 && abs(offset.cy)==90)
			{
				CPoint PointOffset(PrePoint.x+offset.cx/2,PrePoint.y+offset.cy/2);
				for(j=0;j<32;j++)
					{
						if(m_StoneList[j].m_rectStone.PtInRect(PointOffset) && m_StoneList[j].m_bShow)
							return FALSE;
						else
							continue;
					}	
				return TRUE;
			}
			else
				return FALSE;		
		case MA:
			if( (abs(offset.cx)==50 && abs(offset.cy)==90) ||
			    (abs(offset.cx)==100 && abs(offset.cy)==45) )
			{
				if(abs(offset.cx)==50)
				{
					sign=offset.cy/abs(offset.cy);
					i=PrePoint.y+sign*45;
					CPoint PointOffset(PrePoint.x,i);
					for(j=0;j<32;j++)
						{
							if(m_StoneList[j].m_rectStone.PtInRect(PointOffset) && m_StoneList[j].m_bShow)
								return FALSE;
							else
								continue;
						}	
				}
				else
				{
					sign=offset.cx/abs(offset.cx);
					i=PrePoint.x+sign*45;
					CPoint PointOffset(i,PrePoint.y);
					for(j=0;j<32;j++)
						{
							if(m_StoneList[j].m_rectStone.PtInRect(PointOffset) && m_StoneList[j].m_bShow)
								return FALSE;
							else
								continue;
						}	
				}
				return TRUE;
			}
			else
				return FALSE;
		case JU:
			if( (abs(offset.cx)==0 && abs(offset.cy)!=0) ||
				(abs(offset.cx)!=0 && abs(offset.cy)==0))
			{
				if(offset.cx==0)
				{
					sign=offset.cy/abs(offset.cy);
					for(i=PrePoint.y+sign*45;i!=CurPoint.y;i=i+sign*45)
					{
						CPoint PointOffset(PrePoint.x,i);
						for(j=0;j<32;j++)
						{
							if(m_StoneList[j].m_rectStone.PtInRect(PointOffset) && m_StoneList[j].m_bShow)
								return FALSE;
							else
								continue;
						}
					}
				}
				else
				{
					sign=offset.cx/abs(offset.cx);
					for(i=PrePoint.x+sign*50;i!=CurPoint.x;i=i+sign*50)
					{
						CPoint PointOffset(i,PrePoint.y);
						for(j=0;j<32;j++)
						{
							if(m_StoneList[j].m_rectStone.PtInRect(PointOffset) && m_StoneList[j].m_bShow)
								return FALSE;
							else
								continue;
						}
					}					
				}
				return TRUE;
			}	
			else
				return FALSE;
		case PAO:
			if( (abs(offset.cx)==0 && abs(offset.cy)!=0) ||
				(abs(offset.cx)!=0 && abs(offset.cy)==0))
			{
				if(offset.cx==0)
				{
					sign=offset.cy/abs(offset.cy);
					for(i=PrePoint.y+sign*45;i!=CurPoint.y;i=i+sign*45)
					{
						CPoint PointOffset(PrePoint.x,i);
						for(j=0;j<32;j++)
						{
							if(m_StoneList[j].m_rectStone.PtInRect(PointOffset) && m_StoneList[j].m_bShow)
								count++;
							else
								continue;
						}
					}
				}
				else
				{
					sign=offset.cx/abs(offset.cx);
					for(i=PrePoint.x+sign*50;i!=CurPoint.x;i=i+sign*50)
					{
						CPoint PointOffset(i,PrePoint.y);
						for(j=0;j<32;j++)
						{
							if(m_StoneList[j].m_rectStone.PtInRect(PointOffset) && m_StoneList[j].m_bShow)
								count++;
							else
								continue;
						}
					}					
				}
			int k=KillEnemy(m_StoneList[m_nWhichStone].m_nCol,m_StoneList[m_nWhichStone].m_Row,m_bRedTurn);
			if(count==1 && k>=0)
				return TRUE;
			else
				if(count==0 && k<0)
					return TRUE;
				else
					return FALSE;
			}	
			else
				return FALSE;
		case BING:
			if(m_StoneList[m_nWhichStone].m_bRed)
			{
				if(RedRect.PtInRect(m_StoneList[m_nWhichStone].m_rectStone.CenterPoint()))
				{
					if(offset.cy==45 && offset.cx==0)
						return TRUE;
					else
						return FALSE;
				}
				else
					if( (offset.cy==45 && offset.cx==0) || 
						(offset.cy==0 && abs(offset.cx)==50) )
						return TRUE;
					else
						return FALSE;
			}
			else
			{	
				if(BlackRect.PtInRect(m_StoneList[m_nWhichStone].m_rectStone.CenterPoint()))
				{
					if(offset.cy==-45 && offset.cx==0)
						return TRUE;
					else
						return FALSE;
				}
				else
					if( (offset.cy==-45 && offset.cx==0) || 
						(offset.cy==0 && abs(offset.cx)==50) )
						return TRUE;
					else
						return FALSE;						
			}
		default:
			return TRUE;
	}
}

void CMyView::Rules()
{
	MessageBox("违反规则!");
}

BOOL CMyView::FaceToFace()
{
	if(m_StoneList[20].m_rectStone.CenterPoint().x==m_StoneList[4].m_rectStone.CenterPoint().x)	
	{
		CSize offset(m_StoneList[20].m_rectStone.CenterPoint()-m_StoneList[4].m_rectStone.CenterPoint());
		for( int i=m_StoneList[4].m_rectStone.CenterPoint().y+45;
			i!=m_StoneList[20].m_rectStone.CenterPoint().y;i=i+45 )
		{
			CPoint PointOffset(m_StoneList[4].m_rectStone.CenterPoint().x,i);
			for(int j=0;j<32;j++)
			{
				if(m_StoneList[j].m_rectStone.PtInRect(PointOffset) && m_StoneList[j].m_bShow)
					return FALSE;
				else
					continue;
			}
		}
	return TRUE;
	}
	else
		return FALSE;
}
