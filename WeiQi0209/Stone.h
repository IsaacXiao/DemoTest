#include "windows.h"
#include "stdio.h"

typedef struct
{
	BOOL m_bBlack;
	int CurrentNum;
	RECT m_rectStone;
	BOOL m_bShow;
	int Row;
	int Col;
	BOOL m_bNumShow;
}
Stone;

#define MAX_STONE 361
#define	WM_READY WM_USER+2
#define	WM_RECVSTONE WM_USER+3
int Num;
Stone GameStone[MAX_STONE];
SOCKET m_socketPlay,m_sockPlayClient;
//SOCKET sockPlayConn; //for TCP
SOCKADDR_IN addrToPlay;
int error;//测试错误代码用
char test[200];//测试错误代码用
HINSTANCE hLibrary ;