# Microsoft Developer Studio Generated NMAKE File, Based on ResLib.dsp
!IF "$(CFG)" == ""
CFG=ResLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ResLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ResLib - Win32 Release" && "$(CFG)" != "ResLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ResLib.mak" CFG="ResLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ResLib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ResLib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "ResLib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ResLib.dll"


CLEAN :
	-@erase "$(INTDIR)\ResLib.obj"
	-@erase "$(INTDIR)\ResLib.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ResLib.dll"
	-@erase "$(OUTDIR)\ResLib.exp"
	-@erase "$(OUTDIR)\ResLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RESLIB_EXPORTS" /Fp"$(INTDIR)\ResLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\ResLib.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ResLib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\ResLib.pdb" /machine:I386 /out:"$(OUTDIR)\ResLib.dll" /implib:"$(OUTDIR)\ResLib.lib" 
LINK32_OBJS= \
	"$(INTDIR)\ResLib.obj" \
	"$(INTDIR)\ResLib.res"

"$(OUTDIR)\ResLib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ResLib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ResLib.dll"


CLEAN :
	-@erase "$(INTDIR)\ResLib.obj"
	-@erase "$(INTDIR)\ResLib.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ResLib.dll"
	-@erase "$(OUTDIR)\ResLib.exp"
	-@erase "$(OUTDIR)\ResLib.ilk"
	-@erase "$(OUTDIR)\ResLib.lib"
	-@erase "$(OUTDIR)\ResLib.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RESLIB_EXPORTS" /Fp"$(INTDIR)\ResLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\ResLib.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ResLib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\ResLib.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ResLib.dll" /implib:"$(OUTDIR)\ResLib.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ResLib.obj" \
	"$(INTDIR)\ResLib.res"

"$(OUTDIR)\ResLib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("ResLib.dep")
!INCLUDE "ResLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "ResLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ResLib - Win32 Release" || "$(CFG)" == "ResLib - Win32 Debug"
SOURCE=.\ResLib.c

"$(INTDIR)\ResLib.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ResLib.rc

"$(INTDIR)\ResLib.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

