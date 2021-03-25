#include <windows.h>
#include <commdlg.h>
#include "Stone.h"
#include "shlobj.h"
#define UNTITLED TEXT ("(untitled)")

static OPENFILENAME ofn ;
static char szKeyExt1[] = TEXT(".mwq");

void SetAssociate()
{
    HKEY    hKey;
	char    szKeyEnter[] = TEXT("mwqfile");

	char    szKeyExt2[] = TEXT("mwqfile\\shell\\open\\command");
	char    szParam[] = TEXT("  \"%1\"");
	char	szKeyExt3[] = TEXT("mwqfile\\DefaultIcon");
	char    szExeName[MAX_PATH];
	char	strexe[] = ".exe" ;
	char	*p;
	char	*szIcoName;
	char	szExeNameCopy[MAX_PATH];
    if ( ERROR_SUCCESS == RegCreateKey(HKEY_CLASSES_ROOT, szKeyExt1, &hKey))
    {
        RegSetValueEx(hKey, NULL, 0, REG_SZ, szKeyEnter, sizeof(szKeyEnter));
        RegCloseKey(hKey);
    }
    if ( ERROR_SUCCESS == RegCreateKey(HKEY_CLASSES_ROOT, szKeyExt2, &hKey) )
    {
        GetModuleFileName(NULL, szExeName, sizeof(szExeName));
		strcpy(szExeNameCopy,szExeName);
		p = strstr(szExeNameCopy,strexe);
		*p = '.';
		p++;
		*p = 'i';
		p++;
		*p = 'c';
		p++;
		*p = 'o' ;
		szIcoName = szExeNameCopy;
        lstrcat(szExeName, szParam);
        RegSetValueEx(hKey, NULL, 0, REG_EXPAND_SZ, szExeName, strlen(szExeName) + 1);
        RegCloseKey(hKey);
    }
	if ( ERROR_SUCCESS == RegCreateKey(HKEY_CLASSES_ROOT, szKeyExt3, &hKey) )
	{
		RegSetValueEx(hKey, NULL, 0, REG_SZ, szIcoName, strlen(szIcoName)*sizeof(szIcoName));
        RegCloseKey(hKey);
	}
	SHChangeNotify( SHCNE_ASSOCCHANGED , SHCNF_IDLIST,NULL,NULL);
}

BOOL IsAssociate()
{
    HKEY    hKey;
    
    if ( ERROR_SUCCESS == RegOpenKeyEx(HKEY_CLASSES_ROOT, szKeyExt1, 0, KEY_WRITE, &hKey) )
    {
        RegCloseKey(hKey);
        return TRUE;
    }
    return FALSE;
}

void MyFileInitialize (HWND hwnd)
{
     static TCHAR szFilter[] = TEXT ("MWQ Files (*.MWQ)\0*.MWQ\0\0") ;
     
     ofn.lStructSize       = sizeof (OPENFILENAME) ;
     ofn.hwndOwner         = hwnd ;
     ofn.hInstance         = NULL ;
     ofn.lpstrFilter       = szFilter ;
     ofn.lpstrCustomFilter = NULL ;
     ofn.nMaxCustFilter    = 0 ;
     ofn.nFilterIndex      = 0 ;
     ofn.lpstrFile         = NULL ;          // Set in Open and Close functions
     ofn.nMaxFile          = MAX_PATH ;
     ofn.lpstrFileTitle    = NULL ;          // Set in Open and Close functions
     ofn.nMaxFileTitle     = MAX_PATH ;
     ofn.lpstrInitialDir   = NULL ;
     ofn.lpstrTitle        = NULL ;
     ofn.Flags             = 0 ;             // Set in Open and Close functions
     ofn.nFileOffset       = 0 ;
     ofn.nFileExtension    = 0 ;
     ofn.lpstrDefExt       = TEXT ("mwq") ;
     ofn.lCustData         = 0L ;
     ofn.lpfnHook          = NULL ;
     ofn.lpTemplateName    = NULL ;
}

BOOL MyFileOpenDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
     ofn.hwndOwner         = hwnd ;
     ofn.lpstrFile         = pstrFileName ;
     ofn.lpstrFileTitle    = pstrTitleName  ;
     ofn.Flags             = OFN_HIDEREADONLY  ;
     
     return GetOpenFileName (&ofn) ;
}

BOOL MyFileSaveDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
     ofn.hwndOwner         = hwnd ;
     ofn.lpstrFile         = pstrFileName ;
     ofn.lpstrFileTitle    = pstrTitleName ;
     ofn.Flags             = OFN_OVERWRITEPROMPT ;
     
     return GetSaveFileName (&ofn) ;
}

BOOL MyFileWrite (PTSTR pstrFileName)
{
	FILE *fp;
	int i;
	if((fp=fopen(pstrFileName,"wb"))==NULL)
	{
		MessageBox(NULL,TEXT("无法创建文件!"),TEXT("打开文件错误!"),MB_OK);
		return FALSE;
	}
	if(fwrite(&Num,sizeof(int),1,fp)!=1)
	{
		MessageBox(NULL,TEXT("无法将手数写入文件!"),TEXT("写入文件错误!"),MB_OK);
		return FALSE;
	}
	for(i=1;i<=Num;i++)
	{
		if(fwrite(&GameStone[i],sizeof(Stone),1,fp)!=1)
		{
			MessageBox(NULL,TEXT("无法将棋子写入文件!"),TEXT("写入文件错误!"),MB_OK);
			return FALSE;
		}
	}
	fflush(fp);
	fclose(fp);
	return TRUE;
}

BOOL MyFileRead (PTSTR pstrFileName)
{
	FILE *fp;
	int i;
	fp=fopen(pstrFileName,"rb");
	if(fp==NULL)
	{
		MessageBox(NULL,TEXT("无法创建文件!"),TEXT("打开文件错误!"),MB_OK);
		return FALSE;	
	}
	if( fread(&Num,sizeof(int),1,fp)!=1 )
	{
		MessageBox(NULL,TEXT("无法读取手数!"),TEXT("读取文件错误!"),MB_OK);
		return FALSE;		
	}
	for(i=1;i<=Num;i++)
	{
		if( fread(&GameStone[i],sizeof(Stone),1,fp)!=1 )
		{
			MessageBox(NULL,TEXT("无法读取棋子!"),TEXT("读取文件错误!"),MB_OK);
			return FALSE;		
		}
	}
	return TRUE;
}

void DoCaption (HWND hwnd, TCHAR * szTitleName)
{
     TCHAR szCaption[64 + MAX_PATH] ;
     TCHAR szAppName[] = TEXT ("围棋") ;
     wsprintf (szCaption, TEXT ("%s - %s"), szAppName,
               szTitleName[0] ? szTitleName : UNTITLED) ;
     
     SetWindowText (hwnd, szCaption) ;
}

void OkMessage (HWND hwnd, TCHAR * szMessage, TCHAR * szTitleName)
{
     TCHAR szBuffer[64 + MAX_PATH] ;
	 TCHAR szAppName[] = TEXT ("围棋") ;
     
     wsprintf (szBuffer, szMessage, szTitleName[0] ? szTitleName : UNTITLED) ;
     
     MessageBox (hwnd, szBuffer, szAppName, MB_OK | MB_ICONEXCLAMATION) ;
}
