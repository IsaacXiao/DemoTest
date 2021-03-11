
#include <stdio.h>
//#include <windows.h>
#include <afx.h>

SERVICE_STATUS m_ServiceStatus;
SERVICE_STATUS_HANDLE m_ServiceStatusHandle;
BOOL bRunning=true;
void WINAPI ServiceMain(DWORD argc, LPTSTR *argv);//服务主函数
void WINAPI ServiceCtrlHandler(DWORD Opcode);//服务控制函数
void WINAPI CmdStart(void);//要启动的程序函数
BOOL InstallService();   //安装服务的函数
BOOL DeleteService();    //删除服务的函数

//服务名
const LPTSTR lpServiceName = "ServCtrl";
//查看服务状态的时间间隔
const DWORD dwMilliseconds = 60*1000;
//监视的服务程序名
const CString cstrServName = "dtxy_serv";

int main(int argc, char* argv[])
{
	//printf("\twindows based service demo\n");
	//printf("\tgxisone@hotmail.com\n");
	//if(argc!=3)
	//{
	//	printf("usage: %s -install[remove]",argv[0]);
	//	return 0;
	//}
	//if(strcmp(argv[1],"-install")==0)                    /// install
	//{
	//	if(InstallService())
	//		printf("\n\nService Installed Sucessfully\n");
	//	else
	//		printf("\n\nError Installing Service\n");
	//}
	//else if(strcmp(argv[1],"-remove")==0)    // remove
	//{
	//	if(DeleteService())
	//		printf("\n\nService remove sucessfully\n");
	//	else
	//		printf("\n\nError removing Service\n");
	//} 
	//else
	//{
	//	printf("\nusage: %s -install[remove]\n",argv[0]);
	//	return 0;
	//}

	//在进入点函数里面要完成ServiceMain的初始化，
	//准确点说是初始化一个SERVICE_TABLE_ENTRY结构数组，
	//这个结构记录了这个服务程序里面所包含的所有服务的名称
	//和服务的进入点函数
	SERVICE_TABLE_ENTRY 
		DispatchTable[]={{lpServiceName,ServiceMain},{NULL,NULL}};
	//最后的NULL指明数组的结束
	StartServiceCtrlDispatcher(DispatchTable); 
	return 0;
}

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{
	m_ServiceStatus.dwServiceType = SERVICE_WIN32;
	m_ServiceStatus.dwCurrentState = SERVICE_START_PENDING; 
	m_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	m_ServiceStatus.dwWin32ExitCode = 0; 
	m_ServiceStatus.dwServiceSpecificExitCode = 0; 
	m_ServiceStatus.dwCheckPoint = 0; 
	m_ServiceStatus.dwWaitHint = 0;
	m_ServiceStatusHandle = RegisterServiceCtrlHandler(lpServiceName,ServiceCtrlHandler);
	if (m_ServiceStatusHandle == (SERVICE_STATUS_HANDLE)0)return; 
	m_ServiceStatus.dwCurrentState = SERVICE_RUNNING; //设置服务状态
	m_ServiceStatus.dwCheckPoint = 0; 
	m_ServiceStatus.dwWaitHint = 0; 
	//SERVICE_STATUS结构含有七个成员，它们反映服务的现行状态。
	//所有这些成员必须在这个结构被传递到SetServiceStatus之前正确的设置
	SetServiceStatus (m_ServiceStatusHandle, &m_ServiceStatus);
	bRunning=true;
	//*
	CmdStart(); //启动我们的服务程序
	//*
	return; 
}
void WINAPI ServiceCtrlHandler(DWORD Opcode)//服务控制函数
{
	switch(Opcode) 
	{ 
	case SERVICE_CONTROL_PAUSE:    // we accept the command to pause it
		m_ServiceStatus.dwCurrentState = SERVICE_PAUSED; 
		break; 
	case SERVICE_CONTROL_CONTINUE:  // we got the command to continue
		m_ServiceStatus.dwCurrentState = SERVICE_RUNNING; 
		break; 
	case SERVICE_CONTROL_STOP:   // we got the command to stop this service
		m_ServiceStatus.dwWin32ExitCode = 0; 
		m_ServiceStatus.dwCurrentState = SERVICE_STOPPED; 
		m_ServiceStatus.dwCheckPoint = 0; 
		m_ServiceStatus.dwWaitHint = 0; 
		SetServiceStatus (m_ServiceStatusHandle,&m_ServiceStatus);
		bRunning=false;
		return;
	case SERVICE_CONTROL_INTERROGATE: // 
		break; 
	} 
	SetServiceStatus (m_ServiceStatusHandle,  &m_ServiceStatus);
	return; 
}
/*
BOOL InstallService()   //安装服务函数
{
	char strDir[1024];
	SC_HANDLE schSCManager,schService;
	GetCurrentDirectory(1024,strDir);
	GetModuleFileName(NULL,strDir,sizeof(strDir));

	char chSysPath[1024];
	GetSystemDirectory(chSysPath,sizeof(chSysPath));

	strcat(chSysPath,"\\WindowsMgr.exe");
	if(!CopyFile(strDir,chSysPath,FALSE))printf("Copy file OK\n"); // 把我们的服务程序复制到系统根目录

	strcpy(strDir,chSysPath);
	schSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS); 
	if (schSCManager == NULL) 
	{
		printf("open scmanger failed,maybe you do not have the privilage to do this\n");
		return false;
	}

	LPCTSTR lpszBinaryPathName=strDir;

	schService = CreateService(schSCManager,lpServiceName,"Windows Manger Control", //将服务的信息添加到SCM的数据库
		SERVICE_ALL_ACCESS, // desired access 
		SERVICE_WIN32_OWN_PROCESS, // service type 
		SERVICE_AUTO_START, // start type 
		SERVICE_ERROR_NORMAL, // error control type 
		lpszBinaryPathName, // service's binary 
		NULL, // no load ordering group 
		NULL, // no tag identifier 
		NULL, // no dependencies 
		NULL, // LocalSystem account 
		NULL); // no password 

	if (schService == NULL) 
	{
		printf("faint,we failed just because we invoke createservices failed\n");
		return false; 
	}
	CloseServiceHandle(schService); 
	return true;
}

BOOL DeleteService()
{
	SC_HANDLE schSCManager;
	SC_HANDLE hService;
	schSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);

	char chSysPath[1024];
	GetSystemDirectory(chSysPath,sizeof(chSysPath));
	strcat(chSysPath,"\\WindowsMgr.exe");

	if (schSCManager == NULL) 
	{
		printf("faint,open scmanger failed\n");
		return false; 
	}
	hService=OpenService(schSCManager,lpServiceName,SERVICE_ALL_ACCESS);
	if (hService == NULL) 
	{
		printf("faint,open services failt\n");
		return false;
	}
	if(DeleteFile(chSysPath)==0)
	{
		printf("Dell file Failure !\n");               
		return false;
	}
	else printf("Delete file OK!\n");
	if(DeleteService(hService)==0)
		return false;

	if(CloseServiceHandle(hService)==0)
		return false;
	else
		return true;
}
*/
BOOL ServAlreadyRun( CString & strServName )
{
	LONG lRet = 0;  
	BOOL bRet = FALSE;  
	BOOL bIsRun = FALSE;
	SC_HANDLE hSCM = NULL;              // 服务数据库句柄  
	char *pBuf = NULL;                  // 缓冲区指针  
	DWORD dwBufSize = 0;                // 传入的缓冲长度  
	DWORD dwBufNeed = 0;                // 需要的缓冲长度  
	DWORD dwNumberOfService = 0;        // 返回的服务个数  
	ENUM_SERVICE_STATUS_PROCESS *pServiceInfo = NULL;   // 服务信息  

	// 建立了一个到服务控制管理器的连接，并打开指定的数据库  
	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE | SC_MANAGER_CONNECT);  
	if(NULL == hSCM)  
	{  
		//异常处理
	}  

	// 获取需要的缓冲区大小  
	EnumServicesStatusEx(hSCM, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,   
		NULL, dwBufSize, &dwBufNeed, &dwNumberOfService, NULL, NULL);  

	// 多设置存放1个服务信息的长度  
	dwBufSize = dwBufNeed + sizeof(ENUM_SERVICE_STATUS_PROCESS);  
	pBuf = (char *)malloc(dwBufSize);  

	memset(pBuf, 0, dwBufSize);  

	// 获取服务信息  
	bRet = EnumServicesStatusEx(hSCM, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,   
		(LPBYTE)pBuf, dwBufSize, &dwBufNeed, &dwNumberOfService, NULL, NULL);  
	if(bRet == FALSE)  
	{  
		//异常处理 
	}  
	// 关闭打开的服务句柄  
	bRet = ::CloseServiceHandle(hSCM);  
	if(bRet == FALSE)  
	{  
		//异常处理 
	}   

	pServiceInfo = (LPENUM_SERVICE_STATUS_PROCESS)pBuf;  
	//遍历取得的服务信息  
	for(unsigned int i = 0; i < dwNumberOfService; i++)  
	{ 
		if( CString( pServiceInfo[i].lpServiceName ) == strServName )
		{
			if ( pServiceInfo[i].ServiceStatusProcess.dwCurrentState == 4 )
			{
				bIsRun = TRUE;
				break;
			}
		}
	}  

	free(pBuf);  	

	return bIsRun;
}

void WINAPI CmdStart(void)
{
	//--------------------------------
	//把你的要做成服务启动的程序代码添加到这里
	//那么你的代码就可以作为NT服务启动了
	//--------------------------------
	while ( true )
	{
		if ( !ServAlreadyRun( cstrServName ) )
		{

		}
	}
}
