#include <windows.h>
#include "Stone.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "resource.h"

#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")

#define ID_SHOWNUM 2
#define ID_SHOWCOODINATE 3
#define ID_PRE 0
#define ID_NEXT 1
#define ID_STONESTYLE 4
#define ID_TIMER 5

HACCEL hAccel;
TCHAR  szFileName[MAX_PATH], szTitleName[MAX_PATH] ;
HWND hTimeDlg,hChatDlg;
SYSTEMTIME stBlack,stWhite;
BOOL m_bOver,m_bPlayOnline;
WNDPROC ProOwnDraw[2];
BOOL m_bApplicantReady,m_bAcceptReady,m_bSelBlack;
int cxScreen,cyScreen;
LRESULT CALLBACK OwnDrawWndProc(HWND, UINT, WPARAM, LPARAM) ;
BOOL StoneOn(Stone stone[],int n,POINT point);
void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct,HDC hdc,BOOL m_bOver);
void Triangle (HDC hdc, POINT pt[],BOOL m_bStart);
BOOL CALLBACK AboutDlgProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK TimeDlg(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK OwnDrawWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
void CreateMyTooltip (HWND hwnd,HINSTANCE ghThisInstance);
void MyFileInitialize (HWND hwnd);
BOOL MyFileOpenDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName);
BOOL MyFileSaveDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName);
BOOL MyFileWrite (PTSTR pstrFileName);
BOOL MyFileRead (PTSTR pstrFileName);
void DoCaption (HWND hwnd, TCHAR * szTitleName);
void OkMessage (HWND hwnd, TCHAR * szMessage, TCHAR * szTitleName);
void SetAssociate();
BOOL IsAssociate();
AskConfirmation (HWND hwnd);
SYSTEMTIME SetSec(SYSTEMTIME d); 
BOOL CALLBACK ChatDlgProc(HWND hwndDlg,UINT uMsg, WPARAM wParam, LPARAM lParam);
void OnContextMenu(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
	 TCHAR szAppName[] = TEXT ("围棋") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;
	 RECT rectWnd,rectDlg ;

	 INITCOMMONCONTROLSEX InitCtrlEx;
	 InitCommonControlsEx(&InitCtrlEx);

	 hTimeDlg = NULL;
	 hChatDlg = NULL;
	 m_bApplicantReady = FALSE;
	 m_bAcceptReady = FALSE;
	 m_bPlayOnline = FALSE;

	 if( FALSE==IsAssociate() )
		SetAssociate();
	 wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (hInstance,MAKEINTRESOURCE(IDI_WeiQi)) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
//     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	 wndclass.hbrBackground = (HBRUSH) (COLOR_BTNFACE+1) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;
	 wndclass.lpszMenuName = szAppName;

	 strcpy(szFileName,szCmdLine);

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("错误,窗口创建失败!"), 
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
	 
     cxScreen = GetSystemMetrics (SM_CXSCREEN) ;
     cyScreen = GetSystemMetrics (SM_CYSCREEN)-29 ;

     hwnd = CreateWindow (szAppName, TEXT ("围棋"),                 
                          WS_OVERLAPPEDWINDOW /*& ~WS_MAXIMIZEBOX*/ & ~WS_THICKFRAME ,        
                          0,0,cxScreen,cyScreen,NULL,NULL,hInstance, NULL) ;  

	 hChatDlg = CreateDialog(hInstance,"Chat",hwnd,ChatDlgProc);

	 GetWindowRect(hwnd,&rectWnd);
	 GetWindowRect(hChatDlg,&rectDlg);

	 MoveWindow(hChatDlg,(rectWnd.right-(rectDlg.right-rectDlg.left)-10),
									(rectWnd.bottom-(rectDlg.bottom-rectDlg.top)-50),
									rectDlg.right-rectDlg.left-3,
									rectDlg.bottom-rectDlg.top-3,TRUE) ;

	 ShowWindow (hwnd,iCmdShow) ;
     UpdateWindow (hwnd) ;
     
	 //加载加速键表
	 hAccel = LoadAccelerators( 
		hInstance, MAKEINTRESOURCE(IDR_ACCEL));

	 while (GetMessage (&msg, NULL, 0, 0))
     {
		 if( ( hTimeDlg == 0 || !IsDialogMessage(hTimeDlg,&msg) )
			 && ( hChatDlg == 0 || !IsDialogMessage(hChatDlg,&msg) ) )
		 {
			 if(!TranslateAccelerator( msg.hwnd, hAccel, &msg ))
			 {
				TranslateMessage (&msg) ;
				DispatchMessage (&msg) ; 
			 }
		 }
	 }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     HDC         hdc ;
     PAINTSTRUCT ps ;
     static RECT rectPre,rectNext,rectClient,rectPlate;
	 HFONT hFont,hOldFont;
	 static int m_nRow,CurrentNum;
	 int i,j,r,R,cx,cy;			//r为9个星位实心圈的半径,R为棋子半径
	 static POINT pointD,pointL;
	 static BOOL m_bBlackTurn,m_bCoodinateShow,m_bStart,m_bTurnShow,m_bMyTurn,m_bGlassStyle;
	 HBRUSH hBrush;
	 RECT rectCross;
	 POINT pointCross,pt[3];
	 TCHAR m_bBlackGo[] = TEXT ("黑方行棋");
	 TCHAR m_bWhiteGo[] = TEXT ("白方行棋");
	 TCHAR numCoodinate[2];
	 static int cxChar,cyChar;
	 static HWND hShowNumButton,hShowCoodinate,hPre,hNext,hStoneStyle;
	 static LPDRAWITEMSTRUCT pdis;
	 TCHAR szTimeBlack[10],szTimeWhite[10];
	 static HMENU hMenu;
     static HINSTANCE hInstance ;
	 HDROP hDrop ;
	 DWORD dwSize;
	 //HMENU hSysMenu;
	 HBITMAP hBitmap ;
	 HINSTANCE hLibFun ;
	 typedef void (*ShowStoneProc)(HDC hdc,Stone stone,HINSTANCE hInstance);
	 ShowStoneProc ShowStone;
	 static HWND hWndStatus;

	 switch (message)
     {
     case WM_CREATE:
		  hMenu = GetMenu(hwnd);
		  m_bSelBlack = TRUE;
		  //hSysMenu = GetSystemMenu(hwnd,FALSE); 
		  //DeleteMenu(hSysMenu,SC_MOVE,MF_BYCOMMAND);
          hInstance = ((LPCREATESTRUCT) lParam)->hInstance ;

		  //状态栏
		  hWndStatus=CreateWindowEx(0,STATUSCLASSNAME,"",WS_CHILD|WS_BORDER|WS_VISIBLE,
			  -100,-100,10,10,hwnd,(HMENU)100,hInstance,NULL);
		  if(!hWndStatus)
			 MessageBox(hwnd,TEXT("can't create statusbar!"),TEXT("error_notify"),MB_OK);
		  SendMessage(hWndStatus,SB_SETTEXT,0,(LPARAM)(LPSTR)"Welcome!!");

		  m_bCoodinateShow=FALSE;
		  m_bTurnShow = TRUE;
		  Num=0;
		  m_bBlackTurn=TRUE;
		  m_bGlassStyle = TRUE;
		  GameStone[Num].m_bBlack=FALSE;//对局未开始时,第0手棋的颜色是白色
		  GameStone[Num].CurrentNum=0;
		  cxChar = LOWORD (GetDialogBaseUnits());
		  cyChar = HIWORD (GetDialogBaseUnits());
		  hShowNumButton = CreateWindow(TEXT("BUTTON"),TEXT("显示/隐藏手数"),
			  WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, cxScreen/10,cyScreen/2,20*cxChar,7*cyChar/4,
			  hwnd,(HMENU)ID_SHOWNUM,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		  hStoneStyle = CreateWindow(TEXT("BUTTON"),TEXT("水彩/玻璃棋子"),
			  WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, cxScreen/10,cyScreen/2+3*cyChar,20*cxChar,7*cyChar/4,
			  hwnd,(HMENU)ID_STONESTYLE,((LPCREATESTRUCT)lParam)->hInstance,NULL);	
		  hShowCoodinate = CreateWindow(TEXT("BUTTON"),TEXT("显示坐标"),
			  WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cxScreen/11,cyScreen/2-5*cyChar,20*cxChar,7*cyChar/4,
			  hwnd,(HMENU)ID_SHOWCOODINATE,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		  hPre = CreateWindow(TEXT("BUTTON"),TEXT("后退"),
			  WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_PUSHBUTTON,cxScreen/11,cyScreen/2+10*cyChar,9*cxChar,7*cyChar/4,
			  hwnd,(HMENU)ID_PRE,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		  hNext = CreateWindow(TEXT("BUTTON"),TEXT("前进"),
			  WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_PUSHBUTTON,cxScreen/11+11*cxChar,cyScreen/2+10*cyChar,9*cxChar,7*cyChar/4,
			  hwnd,(HMENU)ID_NEXT,((LPCREATESTRUCT)lParam)->hInstance,NULL);
//  		  ProOwnDraw[0] = (WNDPROC)SetWindowLong(hPre,GWL_WNDPROC,(LONG)OwnDrawWndProc);
//  		  ProOwnDraw[1] = (WNDPROC)SetWindowLong(hNext,GWL_WNDPROC,(LONG)OwnDrawWndProc);
		  stBlack.wHour=stWhite.wHour=1;
		  stBlack.wMinute=stWhite.wMinute=stBlack.wSecond=stWhite.wSecond=0;
		  CreateMyTooltip(hStoneStyle,((LPCREATESTRUCT) lParam)->hInstance);
		  CreateMyTooltip(hPre,((LPCREATESTRUCT) lParam)->hInstance);
		  CreateMyTooltip(hNext,((LPCREATESTRUCT) lParam)->hInstance);
		  CreateMyTooltip(hShowCoodinate,((LPCREATESTRUCT) lParam)->hInstance);
		  CreateMyTooltip(hShowNumButton,((LPCREATESTRUCT) lParam)->hInstance);
		  m_bStart=FALSE;
		  MyFileInitialize (hwnd) ;
		  i = strlen(szFileName);
		  szFileName[i-1] = '\0';
		  for(j=0;j<i;j++)
			  szFileName[j] = szFileName[j+1];
		  if(szFileName[0]!='\0')
			  //SendMessage(hwnd,WM_COMMAND,IDM_OPEN,0);
			  //MessageBox(NULL,(LPCTSTR)szFileName,TEXT("File Name"), MB_OK);
			  if(MyFileRead (szFileName) == FALSE)
				  MessageBox(NULL,TEXT("读取文件错误!"),TEXT("读取文件错误!"),MB_OK);	
          GetFileTitle(szFileName,szTitleName,sizeof(szTitleName));		
		  DoCaption (hwnd, szTitleName) ;	
		  DragAcceptFiles(hwnd,TRUE);
		  if ((hLibrary = LoadLibrary ("RESLIB.DLL")) == NULL)
          {
               MessageBox (hwnd, "Can't load RESLIB.DLL.",
                           "错误", 0) ;
               return -1 ;
          }
//   		  if(TRUE)
//   			MessageBox(NULL, "程序正在启动", "提示信息", MB_OK);

          return 0 ;
	 
	 case WM_DROPFILES:
		  hDrop = (HDROP) wParam;
		  dwSize = DragQueryFile(hDrop,0,NULL,0);
		  DragQueryFile(hDrop,0,szFileName,dwSize+1);
          if (!MyFileRead (szFileName))
		  {
              OkMessage (hwnd, TEXT ("Could not read file %s!"),
                                    szTitleName) ;
              szFileName[0]  = '\0' ;
              szTitleName[0] = '\0' ;
          }
		  GetFileTitle(szFileName,szTitleName,sizeof(szTitleName));
		  DoCaption (hwnd, szTitleName) ;
		  DragFinish(hDrop);
		  InvalidateRect(hwnd,NULL,FALSE);
		  return 0;	

	 case WM_TIMER:
		  if(m_bStart)
		  {
			if(m_bBlackTurn)
				stBlack=SetSec(stBlack);//轮到黑行棋时,黑倒计时
			else
				stWhite=SetSec(stWhite);//轮到白行棋时,白倒计时
			m_bTurnShow = !m_bTurnShow; //提示行棋方字体的闪烁效果

			InvalidateRect(hwnd,NULL,FALSE);
		  }
		  return 0;

	 case WM_DRAWITEM:
		  pdis = (LPDRAWITEMSTRUCT) lParam;
		  if(pdis->CtlID==ID_PRE || pdis->CtlID==ID_NEXT)
		  {
			  DrawItem(pdis,pdis->hDC,m_bOver);
			  cx = pdis->rcItem.right  - pdis->rcItem.left ;
			  cy = pdis->rcItem.bottom - pdis->rcItem.top  ;
			  if(pdis->CtlID == ID_PRE)
			  {
				   pt[0].x = cx / 3 ;  pt[0].y =  cy /2 ;
				   pt[1].x = 2 * cx / 3 ;  pt[1].y = 1 * cy / 3 ;
				   pt[2].x = 2 * cx / 3 ;  pt[2].y = 2 * cy / 3 ;
				   Triangle (pdis->hDC, pt,m_bStart) ;
			  }
			  else
				  if(pdis->CtlID == ID_NEXT)
			  {
				   pt[0].x =  cx / 3 ;  pt[0].y = 1 * cy / 3 ;
				   pt[1].x = 1 * cx / 3 ;  pt[1].y = 2 * cy / 3 ;
				   pt[2].x = 2 * cx / 3 ;  pt[2].y = 1 * cy / 2 ;
               
				   Triangle (pdis->hDC, pt,m_bStart) ;
			  }	
			  
			  if (pdis->itemState & ODS_SELECTED)
				  InvertRect (pdis->hDC, &pdis->rcItem) ;
			  if (pdis->itemState & ODS_FOCUS)
			  {
				   pdis->rcItem.left   += cx / 16 ;
				   pdis->rcItem.top    += cy / 8 ;
				   pdis->rcItem.right  -= cx / 16 ;
				   pdis->rcItem.bottom -= cy / 8 ;
               
				   DrawFocusRect (pdis->hDC, &pdis->rcItem) ;
			  }		
		  }
		  break;

	 case WM_COMMAND:
		  switch (wParam)
		  {
		  case 1001:
			   SendMessage(hwnd, WM_COMMAND, ID_SHOWNUM, 0);
			   break;
		  case 1002:
			   SendMessage(hwnd, WM_COMMAND, ID_SHOWCOODINATE, 0);
			   break;
		  case 1003:
			   SendMessage(hwnd, WM_COMMAND, ID_STONESTYLE, 0);
			   break;
		  case IDM_OPEN:
			   if (MyFileOpenDlg (hwnd, szFileName, szTitleName))
			   {
				   if (!MyFileRead(szFileName))
				   {
					   OkMessage (hwnd, TEXT ("Could not read file %s!"),
						   szTitleName) ;
					   szFileName[0]  = '\0' ;
					   szTitleName[0] = '\0' ;
				   }
			   }	
			   DoCaption (hwnd, szTitleName) ;		
			   break;
		  case IDM_SAVE:
               if (MyFileSaveDlg (hwnd, szFileName, szTitleName))
               {
                    DoCaption (hwnd, szTitleName) ;
                    if (MyFileWrite (szFileName))
                         return 1 ;
                    else
                    {
                         OkMessage (hwnd, TEXT ("Could not write file %s"),
                                    szTitleName) ;
                         return 0 ;	
                   }	
               }
			   break;
		  case ID_STONESTYLE:
			   if( BST_CHECKED == SendMessage(hStoneStyle,BM_GETCHECK,0,0) )
			   {
				   m_bGlassStyle = TRUE;
				   SendMessage(hStoneStyle,BM_SETCHECK,0,0);
			   }
			   else
				   if(BST_UNCHECKED == SendMessage(hStoneStyle,BM_GETCHECK,0,0))
				   {
						m_bGlassStyle = FALSE;
					    SendMessage(hStoneStyle,BM_SETCHECK,1,0);
				   }
			   InvalidateRect(hwnd,NULL,TRUE);
			   break;
		  case ID_SHOWNUM:
			   if( BST_CHECKED == SendMessage(hShowNumButton,BM_GETCHECK,0,0) )
			   {
				for(i=1;i<=Num;i++)
					GameStone[i].m_bNumShow = FALSE;
				SendMessage(hShowNumButton,BM_SETCHECK,0,0);
			   }
			   else
				   if(BST_UNCHECKED == SendMessage(hShowNumButton,BM_GETCHECK,0,0))
				   {
						for(i=1;i<=Num;i++)
							GameStone[i].m_bNumShow = TRUE;
					    SendMessage(hShowNumButton,BM_SETCHECK,1,0);
				   }
			   InvalidateRect(hwnd,NULL,TRUE);
			   break;	
		  case ID_SHOWCOODINATE:
			   if(m_bCoodinateShow)
			   {
					m_bCoodinateShow = !m_bCoodinateShow;
					SetWindowText(hShowCoodinate,TEXT("显示坐标"));
			   }
				  else
				  {
				      m_bCoodinateShow = !m_bCoodinateShow;
					  SetWindowText(hShowCoodinate,TEXT("隐藏坐标"));
				  }
			   InvalidateRect(hwnd,NULL,TRUE);
			   break;
		  case ID_PRE:
			   if(Num>0)
			   {
					m_bBlackTurn= !m_bBlackTurn;
				    GameStone[Num].m_bShow=FALSE;
					Num--;
			   }
			   InvalidateRect(hwnd,NULL,TRUE);
			   break;
		  case ID_NEXT:
			   if(Num<CurrentNum)
			   {
					Num++;
					GameStone[Num].m_bShow=TRUE;
					m_bBlackTurn= !m_bBlackTurn;
			   }
			   InvalidateRect(hwnd,NULL,TRUE);
			   break;
		  case IDM_START:
			   m_bPlayOnline = TRUE;
			   m_bBlackTurn=TRUE;
			   m_bStart = TRUE;
			   for(i=Num;i>=1;i--)
			   {
				   GameStone[i].m_bShow = FALSE;
				   Num--;
			   }
			   
			   if(m_bPlayOnline)
				   if(m_bSelBlack)//假设本人选择了黑方
					   m_bMyTurn = m_bSelBlack;
				   else
					   m_bMyTurn = m_bSelBlack;
				   
			   EnableMenuItem(hMenu,IDM_TIME,MF_GRAYED);
			   EnableMenuItem(hMenu,IDM_START,MF_GRAYED);
			   EnableMenuItem(hMenu,IDM_END,MF_ENABLED);
			   EnableWindow(hPre,FALSE);
			   EnableWindow(hNext,FALSE);
			   DrawMenuBar(hwnd);
			   SetTimer(hwnd,ID_TIMER,1000,NULL);
			   InvalidateRect(hwnd,NULL,TRUE);
			   break;
		  case IDM_END:
			   m_bPlayOnline = FALSE;
			   m_bStart = FALSE;
			   m_bBlackTurn = !GameStone[Num].m_bBlack;
			   EnableWindow(hPre,TRUE);
			   EnableWindow(hNext,TRUE);
			   EnableMenuItem(hMenu,IDM_END,MF_GRAYED);
			   EnableMenuItem(hMenu,IDM_TIME,MF_ENABLED);
			   DrawMenuBar(hwnd);
			   m_bTurnShow = TRUE;
			   InvalidateRect(hwnd,NULL,TRUE);
			   break;
          case IDM_APP_ABOUT :
               DialogBox (hInstance, TEXT ("AboutWeiQi"), hwnd, AboutDlgProc) ;
			   InvalidateRect(hwnd,NULL,TRUE);
               break ;
		  case IDM_TIME:
			   hTimeDlg = CreateDialog(hInstance,TEXT("TIMESET"),hwnd,TimeDlg);
			   break;
		  }		  
		  break;
     case WM_PAINT:
		  hdc = BeginPaint (hwnd, &ps) ;
		  GetClientRect (hwnd, &rectClient) ;
		  SetViewportOrgEx(hdc,rectClient.right/2,rectClient.bottom/2,NULL);

		  //hBrush=CreateHatchBrush(HS_DIAGCROSS,RGB(255,255,0));
		  //hBitmap = LoadBitmap (hInstance,MAKEINTRESOURCE(IDB_BOARD)) ;
		  hBitmap = LoadBitmap (hLibrary,MAKEINTRESOURCE(IDB_BOARD)) ;
		  hBrush = CreatePatternBrush (hBitmap) ;
		  DeleteObject (hBitmap) ;

		  m_nRow=cyScreen/24;
		  rectPlate.left=-9*m_nRow;
		  rectPlate.right=9*m_nRow;
		  rectPlate.top=-9*m_nRow;
		  rectPlate.bottom=9*m_nRow;
		  FillRect(hdc,&rectPlate,hBrush);
		  r=5;
		  for(i=0;i<=18;i++)
		  {
			MoveToEx(hdc,rectPlate.left,rectPlate.top+i*m_nRow,NULL);
			LineTo(hdc,rectPlate.right,rectPlate.top+i*m_nRow);
			MoveToEx(hdc,rectPlate.left+i*m_nRow,rectPlate.top,NULL);
			LineTo(hdc,rectPlate.left+i*m_nRow,rectPlate.bottom);
		  }

		  hBrush=GetStockObject(BLACK_BRUSH);
		  SelectObject(hdc,hBrush);
		  Ellipse(hdc,rectPlate.left+3*m_nRow-r,rectPlate.top+3*m_nRow-r,rectPlate.left+3*m_nRow+r,rectPlate.top+3*m_nRow+r);
		  Ellipse(hdc,rectPlate.left+9*m_nRow-r,rectPlate.top+3*m_nRow-r,rectPlate.left+9*m_nRow+r,rectPlate.top+3*m_nRow+r);
		  Ellipse(hdc,rectPlate.left+15*m_nRow-r,rectPlate.top+3*m_nRow-r,rectPlate.left+15*m_nRow+r,rectPlate.top+3*m_nRow+r);
		  Ellipse(hdc,rectPlate.left+3*m_nRow-r,rectPlate.top+9*m_nRow-r,rectPlate.left+3*m_nRow+r,rectPlate.top+9*m_nRow+r);
		  Ellipse(hdc,rectPlate.left+9*m_nRow-r,rectPlate.top+9*m_nRow-r,rectPlate.left+9*m_nRow+r,rectPlate.top+9*m_nRow+r);
		  Ellipse(hdc,rectPlate.left+15*m_nRow-r,rectPlate.top+9*m_nRow-r,rectPlate.left+15*m_nRow+r,rectPlate.top+9*m_nRow+r);
		  Ellipse(hdc,rectPlate.left+3*m_nRow-r,rectPlate.top+15*m_nRow-r,rectPlate.left+3*m_nRow+r,rectPlate.top+15*m_nRow+r);
		  Ellipse(hdc,rectPlate.left+9*m_nRow-r,rectPlate.top+15*m_nRow-r,rectPlate.left+9*m_nRow+r,rectPlate.top+15*m_nRow+r);
		  Ellipse(hdc,rectPlate.left+15*m_nRow-r,rectPlate.top+15*m_nRow-r,rectPlate.left+15*m_nRow+r,rectPlate.top+15*m_nRow+r);

		  hFont=CreateFont(50,0,0,0,400,FALSE,FALSE,0,OEM_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
			  DEFAULT_QUALITY,DEFAULT_PITCH,"仿宋体");
		  hOldFont=SelectObject(hdc,hFont);
		  SetBkColor(hdc,GetSysColor(COLOR_BTNFACE));
		  SetTextColor(hdc,GetSysColor(COLOR_WINDOWTEXT));
		  if(m_bTurnShow)
			TextOut(hdc,-cxScreen*2/5-12,-cyScreen/3+24, (m_bBlackTurn ? m_bBlackGo:m_bWhiteGo), strlen(m_bBlackGo) );	
		  SelectObject(hdc,hOldFont);		
		  
		  if(m_bCoodinateShow)
		  {
			for(i=0;i<=18;i++)
			{
				sprintf(numCoodinate,"%2d",i+1);
				TextOut(hdc,rectPlate.left-m_nRow,rectPlate.top+i*m_nRow-m_nRow/4,numCoodinate,strlen(numCoodinate));
				sprintf(numCoodinate,"%c",'A'+i);
				TextOut(hdc,rectPlate.left+i*m_nRow-m_nRow/9,rectPlate.top-m_nRow*7/9,numCoodinate,strlen(numCoodinate));
			}
		  }

		  hFont=CreateFont(25,0,0,0,0,FALSE,FALSE,0,GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
			  DEFAULT_QUALITY,DEFAULT_PITCH,"楷体_GB2312");
		  hOldFont=SelectObject(hdc,hFont);
		  sprintf(szTimeBlack,"%02u:%02u:%02u",stBlack.wHour,stBlack.wMinute,stBlack.wSecond);
		  sprintf(szTimeWhite,"%02u:%02u:%02u",stWhite.wHour,stWhite.wMinute,stWhite.wSecond);
		  SetTextColor(hdc,RGB(255,0,255));
		  TextOut(hdc,cxScreen*1/3-24,-cyScreen*1/3,TEXT("黑方时间剩余"),strlen("黑方时间剩余"));
		  TextOut(hdc,cxScreen*1/3,-cyScreen*1/3+3*cyChar,szTimeBlack,strlen(szTimeBlack));
		  TextOut(hdc,cxScreen*1/3-24,-cyScreen*1/3+9*cyChar,TEXT("白方时间剩余"),strlen("白方时间剩余"));
		  TextOut(hdc,cxScreen*1/3,-cyScreen*1/3+12*cyChar,szTimeWhite,strlen(szTimeWhite));
		  DeleteObject(SelectObject(hdc,hOldFont));

		  //*********************动态连编加载!!!!
		  if( (hLibFun = LoadLibrary("FUNLIB.DLL")) == NULL)
			  MessageBox(NULL,"无法载入FunLib.dll","错误提示",0);
		  if(m_bGlassStyle)
			  ShowStone = (ShowStoneProc)GetProcAddress(hLibFun,"ShowStoneGlass");
		  else
			  ShowStone = (ShowStoneProc)GetProcAddress(hLibFun,"ShowStoneDraw");
		  if(!ShowStone)
			  MessageBox(NULL,"获取函数地址失败!","错误提示",0);

		  for(i=1;i<=Num;i++)
			  ShowStone(hdc,GameStone[i],hInstance);
		  FreeLibrary(hLibFun);
		  
		  EndPaint (hwnd, &ps) ;
		  return 0 ;

	 case WM_MOUSEMOVE:
		  pointD.x=LOWORD(lParam);
		  pointD.y=HIWORD(lParam);
		  pointL.x=pointD.x-cxScreen/2;
		  pointL.y=pointD.y-cyScreen/2+30;
		  if(PtInRect(&rectPlate,pointL))
			  SetCursor(LoadCursor(hInstance,MAKEINTRESOURCE(IDC_MY)));
		  if(StoneOn(GameStone,Num,pointL))
			  SetCursor(LoadCursor(NULL,IDC_NO));
		  return 0;
	 case WM_RECVSTONE:
		  R=m_nRow/2-3;//棋子半径
		  GameStone[Num+1].m_bBlack=!GameStone[Num].m_bBlack;
		  m_bBlackTurn=!m_bBlackTurn;
		  Num++;
		  //求出GameStone[Num].m_rectStone
		  i = (int)wParam;//GameStone[Num].Row
		  j = (int)lParam;//GameStone[Num].Col
		  pointCross.x=rectPlate.left+j*m_nRow;
		  pointCross.y=rectPlate.top+i*m_nRow;	  

		  GameStone[Num].m_rectStone.left=pointCross.x-R;
		  GameStone[Num].m_rectStone.right=pointCross.x+R;
		  GameStone[Num].m_rectStone.top=pointCross.y-R;
		  GameStone[Num].m_rectStone.bottom=pointCross.y+R;
		  GameStone[Num].CurrentNum=Num;
		  GameStone[Num].m_bShow = TRUE;
		  CurrentNum=Num;

		  InvalidateRect(hwnd,NULL,FALSE);

		  return 0;

	 case WM_CONTEXTMENU:
		  if(!PtInRect(&rectPlate,pointL))
			OnContextMenu(hwnd, message, wParam, lParam);
		  return 0;

	 case WM_LBUTTONDOWN:
		  R=m_nRow/2-3;//棋子半径		  
		 
		  if(m_bPlayOnline)
		  {
			 if(m_bMyTurn != m_bBlackTurn)//不是轮到本方行棋时,点击左键无法走棋
				return 0;
		  }

		  GameStone[Num+1].m_bBlack=!GameStone[Num].m_bBlack;
		  m_bBlackTurn=!m_bBlackTurn;
		  Num++;

		  for(i=0;i<19;i++)
		  {
			  for(j=0;j<19;j++)
			  {
				pointCross.x=rectPlate.left+j*m_nRow;
				pointCross.y=rectPlate.top+i*m_nRow;
				rectCross.left=pointCross.x-R;
				rectCross.right=pointCross.x+R;
				rectCross.top=pointCross.y-R;
				rectCross.bottom=pointCross.y+R;
				if(PtInRect(&rectCross,pointL) && !StoneOn(GameStone,Num,pointL))
				//如果鼠标指向棋盘格子交叉点,并且鼠标没点在已有棋子上
				{
					GameStone[Num].m_bShow=TRUE;
					break;
				}
			  }
			  if(GameStone[Num].m_bShow)
				break;
		  }
		  if(GameStone[Num].m_bShow==FALSE)
		  {
			  GameStone[Num].m_bBlack=!GameStone[Num].m_bBlack;
			  m_bBlackTurn=!m_bBlackTurn;
			  Num--;
			  if(PtInRect(&rectPlate,pointL))
				PlaySound (MAKEINTRESOURCE(IDR_MOVEERROR),hLibrary, SND_RESOURCE | SND_ASYNC) ;
			  return 0;
		  }
		  GameStone[Num].Row = i;
		  GameStone[Num].Col = j;
		  GameStone[Num].m_rectStone.left=pointCross.x-R;
		  GameStone[Num].m_rectStone.right=pointCross.x+R;
		  GameStone[Num].m_rectStone.top=pointCross.y-R;
		  GameStone[Num].m_rectStone.bottom=pointCross.y+R;
		  GameStone[Num].CurrentNum=Num;
		  CurrentNum=Num;

		  if(m_bPlayOnline)
			  //send(m_sockPlayClient,(char *)&GameStone[Num],sizeof(Stone),0);//for TCP
			  //for UDP
		  {
			  sendto(m_sockPlayClient,(char*)&GameStone[Num],sizeof(Stone),0,
			  (SOCKADDR*)&addrToPlay,sizeof(SOCKADDR));
			  error = WSAGetLastError();
			  sprintf(test,"鼠标左键走棋发送时,错误代码为%d",error);
			  if(0!=error)
				  MessageBox(NULL,test,"错误提示!",MB_OK);
		  }
		  PlaySound (MAKEINTRESOURCE(IDR_MOVE),hLibrary, SND_RESOURCE | SND_ASYNC) ;		  		  
		  InvalidateRect(hwnd,NULL,FALSE);
		  return 0;
	 case WM_READY:
		  m_bApplicantReady = (BOOL)wParam;//本方同意状态
		  m_bAcceptReady = (BOOL)lParam;//对方同意状态(收到本方申请了没?)
		  if(m_bApplicantReady && m_bAcceptReady)
		  {
			  m_bPlayOnline = TRUE;
			  EnableMenuItem(hMenu,IDM_START,MF_ENABLED);//对局开始按钮可用
			  DrawMenuBar(hwnd);
			  SendMessage(hwnd,WM_COMMAND,IDM_START,0);//对局开始!
		  }
		  else
		  {
			  m_bPlayOnline = FALSE;
			  EnableMenuItem(hMenu,IDM_START,MF_GRAYED);//对局开始按钮不可用
			  DrawMenuBar(hwnd);		  
		  }
		  return 0;
/*
	 case WM_NCLBUTTONDBLCLK: 
		  if (HTCAPTION==wParam) 
			 return 0; 	
 
	 case WM_KEYDOWN:
		  MessageBox(NULL, "平安无事", "平安无事", MB_OK);
		  return 0;
*/  
	 case WM_CLOSE:
          if (IDYES == AskConfirmation (hwnd))
             DestroyWindow (hwnd) ;
          return 0 ;
     case WM_QUERYENDSESSION:
          if (IDYES == AskConfirmation (hwnd))
              return 1 ;
          else
              return 0 ;
     case WM_DESTROY:
		  FreeLibrary(hLibrary);
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}
