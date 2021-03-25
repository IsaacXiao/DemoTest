# Microsoft Developer Studio Generated NMAKE File, Based on FunLib.dsp
!IF "$(CFG)" == ""
CFG=FunLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to FunLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "FunLib - Win32 Release" && "$(CFG)" != "FunLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FunLib.mak" CFG="FunLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FunLib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FunLib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FunLib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\FunLib.dll"


CLEAN :
	-@erase "$(INTDIR)\FunLib.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FunLib.dll"
	-@erase "$(OUTDIR)\FunLib.exp"
	-@erase "$(OUTDIR)\FunLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FUNLIB_EXPORTS" /Fp"$(INTDIR)\FunLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FunLib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\FunLib.pdb" /machine:I386 /out:"$(OUTDIR)\FunLib.dll" /implib:"$(OUTDIR)\FunLib.lib" 
LINK32_OBJS= \
	"$(INTDIR)\FunLib.obj"

"$(OUTDIR)\FunLib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "FunLib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\FunLib.dll"


CLEAN :
	-@erase "$(INTDIR)\FunLib.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\FunLib.dll"
	-@erase "$(OUTDIR)\FunLib.exp"
	-@erase "$(OUTDIR)\FunLib.ilk"
	-@erase "$(OUTDIR)\FunLib.lib"
	-@erase "$(OUTDIR)\FunLib.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FUNLIB_EXPORTS" /Fp"$(INTDIR)\FunLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ  /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FunLib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\FunLib.pdb" /debug /machine:I386 /out:"$(OUTDIR)\FunLib.dll" /implib:"$(OUTDIR)\FunLib.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\FunLib.obj"

"$(OUTDIR)\FunLib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("FunLib.dep")
!INCLUDE "FunLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "FunLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FunLib - Win32 Release" || "$(CFG)" == "FunLib - Win32 Debug"
SOURCE=.\FunLib.c

"$(INTDIR)\FunLib.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

