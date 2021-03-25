// MyView.h : interface of the CMyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYVIEW_H__FEFB2991_689F_413D_9453_74CA0F9A4F84__INCLUDED_)
#define AFX_MYVIEW_H__FEFB2991_689F_413D_9453_74CA0F9A4F84__INCLUDED_

#include "Stone.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyView : public CView
{
protected: // create from serialization only
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// Attributes
public:
	CMyDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL FaceToFace();
	int m_PreCol;
	int m_PreRow;
	CRect StoneRectPre;
	CRect r;
	void Rules();
	BOOL StoneMoveRules();
	void Area();
	BOOL MoveTo(int col,int row);
	void Go(CPoint point);
	void SelectStone(CPoint point);
	void MoveStone(CPoint point);
	int KillEnemy(int col,int row,BOOL red);
	BOOL KillSelfStone(int col,int row,BOOL red);
	void ShowInfo(CDC *pDC);
	void InitGame();
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CStone m_StoneList[32];
	CPlate m_Plate;
	BOOL m_bRedTurn;
	BOOL m_bSelectOne;
	int m_nWhichStone;
	CRect m_rectInfo;
};

#ifndef _DEBUG  // debug version in MyView.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYVIEW_H__FEFB2991_689F_413D_9453_74CA0F9A4F84__INCLUDED_)
