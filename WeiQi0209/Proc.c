#define  _WIN32_WINNT 0x0500
#include "windows.h"
#include "resource.h"
#include "commctrl.h"
#include "stdio.h"
#include "Stone.h"
extern SYSTEMTIME stBlack,stWhite;
extern HWND hTimeDlg,hChatDlg;
extern BOOL m_bOver;//自绘子窗口鼠标是否停留在上
extern WNDPROC ProOwnDraw[2];
extern BOOL m_bSelBlack;
BOOL m_bConnect,m_bTimeAccept,m_bPlaying;
BOOL m_bFallLine;
SOCKET m_socketFallLine;
extern BOOL m_bApplicantReady,m_bAcceptReady;
static SOCKADDR_IN addrToChat,addrToTime;//TCP则为connect用
SOCKET m_socketChat,m_socketTime,m_sockChatClient,m_sockTimeClient;
//SOCKET sockChatConn,sockTimeConn;	//for TCP
DWORD dwIP;
static int min=0,hour=1;

#define	WM_RECVCHATDATA	WM_USER+1
#define	UM_SOCK WM_USER+4

typedef struct 
{
	BOOL m_bSend;
	int nIDDlgItem;
	SYSTEMTIME d;
}TimeApp;

char* Add(char* str1,char* str2)  
{ 
	char* buf = (char*)malloc(strlen(str1) + strlen(str2) + 1); 
	sprintf(buf,"%s",str1); 
	strcat(buf,str2); 
	return buf; 
}

DWORD WINAPI ChatRecvProc(LPVOID lpParameter)
{
/************************************************************/
//	static SOCKADDR_IN addrFrom;
	SOCKADDR_IN addrFrom;
	int retval;
	HWND hwnd;
	int len;
    char recvBuf[200] ;
	char tempBuf[300] ;
	
	hwnd = (*(HWND*)lpParameter);
	len=sizeof(SOCKADDR);

	//listen(m_socketChat,5);	//for TCP
	//sockChatConn = accept(m_socketChat,(SOCKADDR*)&addrFrom,&len);	//for TCP

	while(m_bConnect)
	{
		retval=recvfrom(m_socketChat,recvBuf,200,0,(SOCKADDR*)&addrFrom,&len);	//for UDP
	//	retval=recv(sockChatConn,recvBuf,200,0);	//for TCP
		if(SOCKET_ERROR==retval)
		{
			error = WSAGetLastError();
			sprintf(test,"聊天线程接收数据时,错误代码为%d",error);
			//MessageBox(NULL,test,"错误提示!",MB_OK);
			break;
		}
		sprintf(tempBuf,"%s说: %s",inet_ntoa(addrFrom.sin_addr),recvBuf);
		PostMessage(hwnd,WM_RECVCHATDATA,(WPARAM)0,(LPARAM)tempBuf);
	}
	return 0;
}

DWORD WINAPI TimeRecvProc(LPVOID lpParameter)
{
	SOCKADDR_IN addrFrom;
	int retval,nID;
	TimeApp appRecv;
	int len=sizeof(SOCKADDR);
	HWND hDlg = (*(HWND*)lpParameter);//这是聊天对话框的句柄!!
	HWND hwndParent = GetParent(hDlg);//这是主(父)窗口的句柄!!
	
	//listen(m_socketTime,5);//for TCP
	//sockTimeConn = accept(m_socketTime,(SOCKADDR*)&addrFrom,&len);//for TCP
	while(m_bTimeAccept)
	{
		//retval=recv(sockTimeConn,(char*)&appRecv,sizeof(TimeApp),0);//for TCP
		retval=recvfrom(m_socketTime,(char*)&appRecv,sizeof(TimeApp),0,(SOCKADDR*)&addrFrom,&len);//for UDP
		/*
		error = WSAGetLastError();
		sprintf(test,"时间线程接收数据时,错误代码为%d",error);
		if(0!=error)
			MessageBox(NULL,test,"错误提示!",MB_OK);
		*/
		appRecv = *(TimeApp*)&appRecv;
		if(SOCKET_ERROR==retval)
			break;
		else
		{
			//m_bSelBlack = !appRecv.m_bSend;
			nID = appRecv.nIDDlgItem;
			min = appRecv.d.wMinute;
			hour = appRecv.d.wHour;
			m_bAcceptReady = TRUE;//对方同意了(收到本方申请了)
			if(nID == 1)//#define IDOK 1 (对方是点了申请按钮而非接受按钮)
			{
				m_bSelBlack = !appRecv.m_bSend;
				SendMessage(hwndParent,WM_COMMAND,IDM_TIME,0);
			}
			else
				if(nID == 1023)//#define IDC_ACCEPT 1023 (对方是点了接受按钮而非申请按钮)
				{
					PostMessage(hwndParent,WM_READY,(WPARAM)m_bApplicantReady,(LPARAM)m_bAcceptReady);
					InvalidateRect(hwndParent,NULL,FALSE);
				}
		}
	}	
	return 0;
}

DWORD WINAPI PlayRecvProc(LPVOID lpParameter)
{
	SOCKADDR_IN addrFrom;
	int retval;
	Stone stoneRecv;
	int len=sizeof(SOCKADDR);
	HWND hDlg = (*(HWND*)lpParameter);//这是聊天对话框的句柄!!
	HWND hwndParent = GetParent(hDlg);//这是主(父)窗口的句柄!!
	
	//listen(m_socketPlay,5);//for TCP
	//sockPlayConn = accept(m_socketPlay,(SOCKADDR*)&addrFrom,&len);//for TCP
	while(m_bPlaying)
	{
		//retval=recv(sockPlayConn,(char*)&stoneRecv,sizeof(Stone),0);//for TCP
		retval=recvfrom(m_socketPlay,(char*)&stoneRecv,sizeof(Stone),0,(SOCKADDR*)&addrFrom,&len);//for UDP
		error = WSAGetLastError();
		/*
		sprintf(test,"走棋线程接收数据时,错误代码为%d",error);
		if(0!=error)
			MessageBox(NULL,test,"错误提示!",MB_OK);
		*/
		stoneRecv = *(Stone*)&stoneRecv;
		if(SOCKET_ERROR==retval)
			break;
		else
		{
			PostMessage(hwndParent,WM_RECVSTONE,(WPARAM)stoneRecv.Row,(LPARAM)stoneRecv.Col);
		}
	}	
	return 0;
}

BOOL CALLBACK ChatDlgProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	//int result;//for TCP
	HANDLE hChatThread ;
	static HMENU hMenu;
	int retval;
	static HWND hwndIP;
	char *str = NULL;
	
	BOOL m_bWantQuit;
	SOCKADDR_IN addrFromFallLine,addrToFallLine;
	WSABUF wsabuf;	
	DWORD dwRead,dwSend;	
	DWORD dwFlag=0;
	
	int textSendLen = 0;
	int textRecvLen = 0;
	char *strSend = NULL; 
	char *strTemp = NULL;
	char *strBuf = NULL;
	static HWND hwndEditSend ;
	static HWND hwndEditRecv ;
	int len = sizeof(SOCKADDR) ;

	SOCKADDR_IN addrSockChat,addrSockTime,addrSockPlay,addrSockFallLine;//为bind用
	HWND hwndParent = GetParent(hwndDlg);
	HANDLE hTimeThread = NULL,hPlayThread = NULL;
		 
	switch(uMsg)
	{
	case WM_INITDIALOG:
		 m_bFallLine = FALSE;
		 m_bWantQuit = FALSE;		
		 m_bApplicantReady = FALSE;
		 m_bAcceptReady = FALSE;
		 hMenu = GetMenu(hwndParent);
		 hwndEditRecv = GetDlgItem(hwndDlg,IDC_EDIT_RECV) ;
		 hwndIP = GetDlgItem(hwndDlg,IDC_IPADDRESS1);
		 EnableWindow(GetDlgItem(hwndDlg,IDC_BTN_CONN),FALSE);
		 return TRUE;

	case WM_RECVCHATDATA:
		 str=(char*)lParam;
		 textRecvLen = GetWindowTextLength(hwndEditRecv);
		 strTemp = (char*)malloc(textRecvLen+1);
		 GetDlgItemText(hwndDlg,IDC_EDIT_RECV,strTemp,textRecvLen+1);

		 str = Add(str,"\r\n");
		 str = Add(str,strTemp);
		 SetDlgItemText(hwndDlg,IDC_EDIT_RECV,str);
		 free(strTemp);
		 return TRUE;
		 
	case UM_SOCK:
		 wsabuf.buf = (char*)&m_bFallLine;
		 wsabuf.len = sizeof(BOOL);
		 if(SOCKET_ERROR==WSARecvFrom(m_socketFallLine,&wsabuf,1,&dwRead,&dwFlag,
						(SOCKADDR*)&addrFromFallLine,&len,NULL,NULL))
		 {
			error = WSAGetLastError();
			MessageBox(NULL,"判掉线接收数据失败!","判掉线接受数据提示",MB_OK);
			return FALSE;
		 }
		 m_bFallLine = *(BOOL*)wsabuf.buf;
		 if(TRUE == m_bFallLine)
		 {
			 MessageBox(NULL,"对方已断开连接或者掉线!","判断线接受数据提示",MB_OK);
			 SendMessage(hwndDlg,WM_COMMAND,IDC_BTN_UNCONNECT,0);
			 return TRUE;
		 }
		 else
			 return FALSE;

	case WM_COMMAND:
		 switch (LOWORD (wParam))
		 {
		 case IDC_BTN_ONLINE:
			  m_bConnect = TRUE;
			  m_bTimeAccept = TRUE;
			  m_bPlaying = TRUE;
			  hwndEditSend = GetDlgItem(hwndDlg,IDC_EDIT_SEND) ;
			  wVersionRequested = MAKEWORD( 2, 2 );
			  err = WSAStartup( wVersionRequested, &wsaData );
			  if ( err != 0 ) 
			  {
				  MessageBox(NULL,"服务版本加载失败!","Winsock服务请求提示",MB_OK);
				  return FALSE;
			  }
			  if ( LOBYTE( wsaData.wVersion ) != 2 ||
				  HIBYTE( wsaData.wVersion ) != 2 ) 
			  {
				  MessageBox(NULL,"服务版本加载失败!","Winsock服务请求提示",MB_OK);
				  WSACleanup( );
				  return FALSE;  
			  }	

			  //m_socketChat = socket (AF_INET, SOCK_STREAM, 0) ;//for TCP
			  m_socketChat=socket(AF_INET,SOCK_DGRAM,0);//for UDP
			  if(INVALID_SOCKET==m_socketChat)
			  {
				  MessageBox(NULL,"聊天套接字创建失败!","聊天套接字创建提示",MB_OK);
				  return FALSE;
			  }
			  addrSockChat.sin_family=AF_INET;
			  addrSockChat.sin_port=htons(6000);
			  addrSockChat.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
			  retval=bind(m_socketChat,(SOCKADDR*)&addrSockChat,sizeof(SOCKADDR));
			  if(SOCKET_ERROR==retval)
			  {
				  closesocket(m_socketChat);
				  MessageBox(NULL,"聊天套接字绑定失败!","聊天套接字绑定提示",MB_OK);
				  return FALSE;
			  }

			  //m_socketTime = socket (AF_INET, SOCK_STREAM, 0) ;//for TCP
			  m_socketTime = socket (AF_INET,SOCK_DGRAM, 0) ;//for UDP
			  if(INVALID_SOCKET==m_socketTime)
			  {
				  MessageBox(NULL,"时间套接字创建失败!","时间套接字创建提示",MB_OK);
				  return FALSE;
			  }
			  addrSockTime.sin_family=AF_INET;
			  addrSockTime.sin_port=htons(6002);
			  addrSockTime.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
			  retval=bind(m_socketTime,(SOCKADDR*)&addrSockTime,sizeof(SOCKADDR));
			  if(SOCKET_ERROR==retval)
			  {
				  closesocket(m_socketTime);
				  MessageBox(NULL,"时间套接字绑定失败!","时间套接字绑定提示",MB_OK);
				  return FALSE;
			  }

			  //m_socketPlay = socket (AF_INET, SOCK_STREAM, 0) ;//for TCP
			  m_socketPlay = socket (AF_INET,SOCK_DGRAM, 0) ;//for UDP
			  if(INVALID_SOCKET==m_socketPlay)
			  {
				  MessageBox(NULL,"下棋套接字创建失败!","下棋套接字创建提示",MB_OK);
				  return FALSE;
			  }
			  addrSockPlay.sin_family=AF_INET;
			  addrSockPlay.sin_port=htons(6004);
			  addrSockPlay.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
			  retval=bind(m_socketPlay,(SOCKADDR*)&addrSockPlay,sizeof(SOCKADDR));
			  if(SOCKET_ERROR==retval)
			  {
				  closesocket(m_socketPlay);
				  MessageBox(NULL,"下棋套接字绑定失败!","下棋套接字绑定提示",MB_OK);
				  return FALSE;
			  }
			  
			  m_socketFallLine = WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,0);
			  
			  if(INVALID_SOCKET==m_socketFallLine)
			  {
				  MessageBox(NULL,"判掉线套接字创建失败!","判掉线套接字创建提示",MB_OK);
				  return FALSE;
			  }
			  
			  addrSockFallLine.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
			  addrSockFallLine.sin_family=AF_INET;
			  addrSockFallLine.sin_port=htons(6006);
			  if(SOCKET_ERROR==bind(m_socketFallLine,(SOCKADDR*)&addrSockFallLine,sizeof(SOCKADDR)))
			  {
				  MessageBox(NULL,"判掉线套接字绑定失败!","判掉线套接字绑定提示",MB_OK);
				  return FALSE;
			  }
			  if(SOCKET_ERROR==WSAAsyncSelect(m_socketFallLine,hwndDlg,UM_SOCK,FD_READ))
			  {
				  MessageBox(NULL,"注册网络读取事件失败!","注册网络读取事件提示",MB_OK);
				  return FALSE;
			  }
			  
			  hChatThread=CreateThread(NULL,0,ChatRecvProc,(LPVOID)&hwndDlg,0,NULL);
			  CloseHandle(hChatThread);	
			  
			  hTimeThread=CreateThread(NULL,0,TimeRecvProc,(LPVOID)&hwndDlg,0,NULL);
			  CloseHandle(hTimeThread);
			  hPlayThread=CreateThread(NULL,0,PlayRecvProc,(LPVOID)&hwndDlg,0,NULL);
			  CloseHandle(hPlayThread);
			  
			  EnableWindow(GetDlgItem(hwndDlg,IDC_BTN_ONLINE),FALSE);
			  EnableWindow(GetDlgItem(hwndDlg,IDC_BTN_CONN),TRUE);
			  SetFocus(hwndParent);
			  return TRUE;
		 case IDC_BTN_CONN:
			  SendMessage(hwndIP,IPM_GETADDRESS, 0, (LPARAM) &dwIP);
			  if(0 != dwIP)
			  {
			 	  //m_sockChatClient = socket(AF_INET, SOCK_STREAM, 0);	//for TCP
				  m_sockChatClient = socket(AF_INET, SOCK_DGRAM, 0); //for UDP
				  addrToChat.sin_family=AF_INET;
				  addrToChat.sin_port=htons(6000);
				  addrToChat.sin_addr.S_un.S_addr=htonl(dwIP);
				  //result = connect(m_sockChatClient, (SOCKADDR *)&addrToChat, sizeof(SOCKADDR));	//for TCP

				  //m_sockTimeClient = socket(AF_INET, SOCK_STREAM, 0);//for TCP
				  m_sockTimeClient = socket(AF_INET,SOCK_DGRAM, 0);//forUDP
				  addrToTime.sin_family=AF_INET;
				  addrToTime.sin_port=htons(6002);
				  addrToTime.sin_addr.S_un.S_addr=htonl(dwIP);
				  //result = connect(m_sockTimeClient, (SOCKADDR *)&addrToTime, sizeof(SOCKADDR));	//for TCP
				  
				  //m_sockPlayClient = socket(AF_INET, SOCK_STREAM, 0);//for TCP
				  m_sockPlayClient = socket(AF_INET, SOCK_DGRAM, 0);//for UDP
				  addrToPlay.sin_family=AF_INET;
				  addrToPlay.sin_port=htons(6004);
				  addrToPlay.sin_addr.S_un.S_addr=htonl(dwIP);
				  //result = connect(m_sockPlayClient, (SOCKADDR *)&addrToPlay, sizeof(SOCKADDR));	//for TCP
				  
				  EnableWindow(GetDlgItem(hwndDlg,IDC_BTN_CONN),FALSE);	
				  EnableMenuItem(hMenu,IDM_TIME,MF_ENABLED);
			  }
			  SetFocus(hwndParent);
			  return TRUE;
		 case IDC_BTN_UNCONNECT:
			  
			  m_bWantQuit = TRUE;
			  wsabuf.buf = (char*)&m_bWantQuit;
			  wsabuf.len = sizeof(BOOL);	  
			  addrToFallLine.sin_family=AF_INET;
			  addrToFallLine.sin_port=htons(6006);
			  addrToFallLine.sin_addr.S_un.S_addr=htonl(dwIP);
			  if(!m_bFallLine)
			  {
				  if(SOCKET_ERROR==WSASendTo(m_socketFallLine,&wsabuf,1,&dwSend,0,
					  (SOCKADDR*)&addrToFallLine,sizeof(SOCKADDR),NULL,NULL))
				  {
					  //MessageBox(NULL,"判掉线发送数据失败!","判掉线发送数据提示",MB_OK);
					  error = WSAGetLastError();
					  return FALSE;
				  }
				  m_bFallLine = FALSE;
			  }
			  			  
			  EnableMenuItem(hMenu,IDM_TIME,MF_GRAYED);
			  EnableMenuItem(hMenu,IDM_START,MF_GRAYED);
			  EnableWindow(GetDlgItem(hwndDlg,IDC_BTN_ONLINE),TRUE);
			  EnableWindow(GetDlgItem(hwndDlg,IDC_BTN_CONN),TRUE);
			  
			  hChatThread = NULL;	
			  //closesocket(sockChatConn);//服务器端连接状态的
			  closesocket(m_socketChat);//服务器端监听状态的
			  closesocket(m_sockChatClient);//客户端连接状态的
			  m_bConnect = FALSE;//结束线程
			  //sockChatConn = 0;
			  m_socketChat = 0;
			  m_sockChatClient = 0;

			  hTimeThread = NULL;	
			  //closesocket(sockTimeConn);//服务器端连接状态的
			  closesocket(m_socketTime);//服务器端监听状态的
			  closesocket(m_sockTimeClient);//客户端连接状态的
			  m_bTimeAccept = FALSE;//结束线程
			  //sockTimeConn = 0;
			  m_socketTime = 0;
			  m_sockTimeClient = 0;

			  hPlayThread = NULL;	
			  //closesocket(sockPlayConn);//服务器端连接状态的
			  closesocket(m_socketPlay);//服务器端监听状态的
			  closesocket(m_sockPlayClient);//客户端连接状态的
			  m_bPlaying = FALSE;//结束线程
			  //sockPlayConn = 0;
			  m_socketTime = 0;
			  m_sockTimeClient = 0;

			  WSACleanup();
			  SetFocus(hwndParent);
			  return TRUE;

		 case IDC_BTN_SEND:
			  textSendLen = GetWindowTextLength(hwndEditSend);
			  strSend = (char*)malloc(textSendLen+1);
			  GetDlgItemText(hwndDlg,IDC_EDIT_SEND,strSend,textSendLen+1);
			//for UDP
			  sendto(m_sockChatClient,strSend,strlen(strSend)+1,0,
				  (SOCKADDR*)&addrToChat,sizeof(SOCKADDR));
			  error = WSAGetLastError();
			  sprintf(test,"点击发送按钮时,错误代码为%d",error);
			  if(0!=error)
				  MessageBox(NULL,test,"错误提示!",MB_OK);			
			  //send(m_sockChatClient,strSend,strlen(strSend)+1,0);	//for TCP
			  SetDlgItemText(hwndDlg,IDC_EDIT_SEND,"");
			  
			  if( !IsWindowEnabled(GetDlgItem(hwndDlg,IDC_BTN_ONLINE)) && m_bConnect )
			  {
				  textRecvLen = GetWindowTextLength(hwndEditRecv);
				  strTemp = (char*)malloc(textRecvLen+1);
				  GetDlgItemText(hwndDlg,IDC_EDIT_RECV,strTemp,textRecvLen+1);
				  strBuf = "你说:";
				  strBuf = Add(strBuf,strSend);
				  strBuf = Add(strBuf,"\r\n");
				  strBuf = Add(strBuf,strTemp);
				  SetDlgItemText(hwndDlg,IDC_EDIT_RECV,strBuf);
				  free(strTemp);
			  }
			  //SetFocus(hwndParent);
			  return TRUE;
		 }
		 break;

	case WM_CLOSE:
		 DestroyWindow(hwndDlg);
		 hChatDlg = NULL;

		 break;
	}
	return FALSE;
}

BOOL CALLBACK TimeDlg(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	HWND hHour,hMin,hSec;
	static HWND hSelect,hwndParent;
	HWND hSelBlack = GetDlgItem(hDlg,IDC_SELBLACK);
	HWND hSelWhite = GetDlgItem(hDlg,IDC_SELWHITE);
	TimeApp appSend;
	int error;

	switch(message)
	{
	case WM_INITDIALOG:
		 hwndParent = GetParent(hDlg);
		 hSelect = GetDlgItem(hDlg,IDC_SELBLACK);
		 hHour = GetDlgItem(hDlg,IDC_HOUR);
		 hMin = GetDlgItem(hDlg,IDC_MIN);
		 hSec = GetDlgItem(hDlg,IDC_SEC);
		 SendMessage(hHour,EM_LIMITTEXT,1,0);
		 SendMessage(hMin,EM_LIMITTEXT,2,0);
		 SendMessage(hSec,EM_LIMITTEXT,2,0);
		 SetDlgItemInt(hDlg,IDC_HOUR,hour,FALSE);
		 SetDlgItemInt(hDlg,IDC_MIN,min,FALSE);
		 SetDlgItemInt(hDlg,IDC_SEC,0,FALSE);
		 if(m_bSelBlack)
			CheckRadioButton(hDlg,IDC_SELBLACK,IDC_SELWHITE,IDC_SELBLACK);
		 else
			CheckRadioButton(hDlg,IDC_SELBLACK,IDC_SELWHITE,IDC_SELWHITE);
		 return TRUE;
    case WM_COMMAND :
         switch (LOWORD (wParam))
         {
         case IDOK :
			  if( BST_CHECKED == SendMessage(hSelect,BM_GETCHECK,0,0) )
				  m_bSelBlack = TRUE;
			  else
				  m_bSelBlack = FALSE;
			  if(hour==0 && min==0)
			  {
				MessageBox(hDlg,TEXT("请重新输入!"),TEXT("错误"),MB_OK);
				return FALSE;
			  }
			  
			  stBlack.wMinute = stWhite.wMinute = min;
			  stBlack.wHour = stWhite.wHour = hour;
			  stBlack.wSecond = stWhite.wSecond = 0;
			  
			  appSend.m_bSend = m_bSelBlack;
			  appSend.nIDDlgItem = IDOK;
			  appSend.d = stWhite;//设置好的时间
			  //send(m_sockTimeClient,(char *)&appSend,sizeof(TimeApp),0);	//for TCP
			  //for UDP
			  sendto(m_sockTimeClient,(char *)&appSend,sizeof(TimeApp),0,
				  (SOCKADDR*)&addrToTime,sizeof(SOCKADDR));
			  error = WSAGetLastError();
			  sprintf(test,"时间对话框点击申请按钮时,错误代码为%d",error);
			  if(0!=error)
				  MessageBox(NULL,test,"错误提示!",MB_OK);

			  m_bApplicantReady = TRUE;//本方准备好了
			  m_bAcceptReady = FALSE;//征得对方同意
			  DestroyWindow(hDlg);
			  hTimeDlg = NULL;
			  return TRUE;
			  
		 case IDC_ACCEPT:
			  stBlack.wMinute = stWhite.wMinute = min;
			  stBlack.wHour = stWhite.wHour = hour;
			  stBlack.wSecond = stWhite.wSecond = 0;
			  InvalidateRect(hwndParent,NULL,FALSE);

			  m_bApplicantReady = TRUE;//本方同意了
			  PostMessage(hwndParent,WM_READY,(WPARAM)m_bApplicantReady,(LPARAM)m_bAcceptReady);
			  appSend.m_bSend = m_bSelBlack;
			  appSend.nIDDlgItem = IDC_ACCEPT;
			  appSend.d = stWhite;
			  //send(m_sockTimeClient,(char *)&appSend,sizeof(TimeApp),0);//for TCP
			  sendto(m_sockTimeClient,(char *)&appSend,sizeof(TimeApp),0,
				  (SOCKADDR*)&addrToTime,sizeof(SOCKADDR));			  
			  if( BST_CHECKED == SendMessage(hSelect,BM_GETCHECK,0,0) )
				  m_bSelBlack = TRUE;
			  else
				  m_bSelBlack = FALSE;
			  DestroyWindow(hDlg);
			  hTimeDlg = NULL;
			  return TRUE;		 
         case IDCANCEL:
			  m_bApplicantReady = FALSE;
			  m_bAcceptReady = FALSE;
			  PostMessage(hwndParent,WM_READY,(WPARAM)m_bApplicantReady,(LPARAM)m_bAcceptReady);
			  DestroyWindow(hDlg);
			  hTimeDlg = NULL;
			  return TRUE;
		 case IDC_HOUR:
			  hour = GetDlgItemInt(hDlg,IDC_HOUR,NULL,FALSE);
			  return TRUE;
		 case IDC_MIN:
			  min = GetDlgItemInt(hDlg,IDC_MIN,NULL,FALSE);
			  if(HIWORD(wParam) == EN_CHANGE)
			  {
				  if(min>60)
				{
					MessageBox(hDlg,TEXT("请输入个60以下的数!"),TEXT("错误"),MB_OK);
					SetDlgItemInt(hDlg,IDC_MIN,0,FALSE);
					return FALSE;
				}
			  }
			  return TRUE;
         }	
		 break;
	case WM_CLOSE:
		 DestroyWindow(hDlg);
		 hTimeDlg = NULL;
		 break;
	}
	return FALSE;
}

LRESULT CALLBACK OwnDrawWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TRACKMOUSEEVENT tme;
	int id = GetWindowLong(hwnd,GWL_ID);
	switch (message)
	{
	case WM_CREATE:
		 m_bOver = FALSE;
		 return 0;
	case WM_MOUSEMOVE:
		 if ( !m_bOver )
		 {
			m_bOver = TRUE;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = hwnd;
			tme.dwFlags = TME_LEAVE ;
			tme.dwHoverTime = 2;
			TrackMouseEvent(&tme);
		 }
		 PlaySound (MAKEINTRESOURCE(IDR_BTNFOCUS),hLibrary, SND_RESOURCE | SND_ASYNC) ;
		 InvalidateRect(hwnd,NULL,TRUE);
		 break;
	case WM_MOUSELEAVE:
		 if ( m_bOver )
		 {
			m_bOver = FALSE;
		 }
		 PlaySound (MAKEINTRESOURCE(IDR_BTNFOCUS),hLibrary, SND_RESOURCE | SND_ASYNC) ;
		 InvalidateRect(hwnd,NULL,FALSE);
		 break;
    }	
	return CallWindowProc (ProOwnDraw[id], hwnd, message, wParam, lParam) ;
}

BOOL CALLBACK AboutDlgProc (HWND hDlg, UINT message, 
                            WPARAM wParam, LPARAM lParam)
{
     int iRet = 34;
	 switch (message)
     {
     case WM_INITDIALOG :
          return TRUE ;
          
     case WM_COMMAND :
          switch (LOWORD (wParam))
          {
          case IDOK :
          case IDCANCEL :
			   ShellExecute(NULL, ("open"), ("http://www.hncspost.com"), NULL, NULL, SW_SHOW);
			   if(iRet > 32)
			  {
				//MessageBox(NULL,("执行成功！"), "结果提示", MB_OK);
			   }
			   else
			  {
			   	MessageBox(NULL,("执行失败！"), "结果提示", MB_OK);
			   }
               EndDialog (hDlg, 0) ;
               return TRUE ;
          }
          break ;
     }
     return FALSE ;
}

AskConfirmation (HWND hwnd)
{
     return MessageBox (hwnd, TEXT ("是否真的退出?"),
                        TEXT("围棋"), MB_YESNO | MB_ICONQUESTION) ;
}

void OnContextMenu(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int nX;
	int nY;

	HMENU hPopMenu = CreatePopupMenu( );

	// 增加菜单项
	AppendMenu( hPopMenu, MF_STRING, 1001, "显示/隐藏手数");
	AppendMenu( hPopMenu, MF_SEPARATOR, 0, NULL );
	AppendMenu( hPopMenu, MF_STRING, 1002, "显示/隐藏坐标");
	AppendMenu( hPopMenu, MF_SEPARATOR, 0, NULL );
	AppendMenu( hPopMenu, MF_STRING, 1003, "玻璃/水彩棋子");

	// 坐标获取
	nX = LOWORD( lParam );
	nY = HIWORD( lParam );
	
	// 显示菜单
	TrackPopupMenu( hPopMenu, TPM_LEFTALIGN,
		nX, nY, 0, hwnd, NULL );

	// 删除菜单
	DestroyMenu( hPopMenu );		 
}
