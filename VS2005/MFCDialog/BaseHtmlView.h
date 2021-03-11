#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CHtmlView。"
#endif 

// CBaseHtmlView Html 视图

class CBaseHtmlView : public CHtmlView
{
	DECLARE_DYNCREATE(CBaseHtmlView)

	

public:
	virtual ~CBaseHtmlView();
	CBaseHtmlView();  

	afx_msg void OnDestroy( );
	afx_msg int OnMouseActivate(
		CWnd* pDesktopWnd,
		UINT nHitTest,
		UINT message );

	afx_msg void OnSize(
		UINT nType,
		int cx,
		int cy 
		);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual void OnInitialUpdate();
	BOOL CreateFromStatic(UINT nID, CWnd* pParent);
};


