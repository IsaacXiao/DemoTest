// BaseHtmlView.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCDialog.h"
#include "BaseHtmlView.h"


// CBaseHtmlView

IMPLEMENT_DYNCREATE(CBaseHtmlView, CHtmlView)

CBaseHtmlView::CBaseHtmlView()
{

}

CBaseHtmlView::~CBaseHtmlView()
{
}

void CBaseHtmlView::OnDestroy( )
{
	if (m_pBrowserApp) 
	{
		m_pBrowserApp.Release();
		m_pBrowserApp = NULL;
	}
	CWnd::OnDestroy(); //为了跳过CView（doc/frame）的OnDestroy
}

int CBaseHtmlView::OnMouseActivate(
CWnd* pDesktopWnd,
UINT nHitTest,
UINT message )
{
		return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message); //为了跳过CView（doc/frame）的OnMouseActivate
}

void CBaseHtmlView::OnSize(
UINT nType,
int cx,
int cy 
)
{
		CFormView::OnSize(nType, cx, cy);

		if (::IsWindow(m_wndBrowser.m_hWnd))
		{
			CRect rect;
			GetClientRect(rect);
			LONG lWindows = GetWindowLong(GetParent()->GetSafeHwnd(), GWL_EXSTYLE);
			/*		::AdjustWindowRectEx(rect, GetStyle(), FALSE, WS_CLIPSIBLINGS);*/
			::AdjustWindowRectEx(rect, GetStyle(), FALSE, lWindows);
			m_wndBrowser.SetWindowPos(NULL, rect.left, rect.top, 962, 632, SWP_NOACTIVATE | SWP_NOZORDER);
		}	
}

BOOL CBaseHtmlView::CreateFromStatic(UINT nID, CWnd* pParent)
{
	CWnd* pStatic = pParent->GetDlgItem(nID);
	if (pStatic == NULL)
		return FALSE;

	CRect rc;
	pStatic->GetWindowRect(&rc);
	pParent->ScreenToClient(&rc);
	pStatic->DestroyWindow();

	if (!CHtmlView::Create(NULL, NULL, (WS_CHILD | WS_VISIBLE), rc, pParent, nID, NULL))
		return FALSE;

	OnInitialUpdate();  //加载网页或html
	SetSilent(TRUE);//add by wh ,bid pop script dlg  true表示允许界面弹出对话框
	return TRUE;	
}

void CBaseHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBaseHtmlView, CHtmlView)
END_MESSAGE_MAP()


// CBaseHtmlView 诊断

#ifdef _DEBUG
void CBaseHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CBaseHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG


// CBaseHtmlView 消息处理程序

void CBaseHtmlView::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	//CHtmlView::PostNcDestroy();   注释掉，防止CView 销毁自己
}

void CBaseHtmlView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	Navigate2(TEXT("http://blog.csdn.net/qq_20828983?viewmode=contents"), NULL, NULL); //这里的网站可以任意更换
}
