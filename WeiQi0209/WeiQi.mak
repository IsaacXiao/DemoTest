# Microsoft Developer Studio Generated NMAKE File, Based on WeiQi.dsp
!IF "$(CFG)" == ""
CFG=WeiQi - Win32 Debug
!MESSAGE No configuration specified. Defaulting to WeiQi - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WeiQi - Win32 Release" && "$(CFG)" != "WeiQi - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WeiQi.mak" CFG="WeiQi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WeiQi - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WeiQi - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "WeiQi - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\WeiQi.exe" "$(OUTDIR)\WeiQi.bsc"


CLEAN :
	-@erase "$(INTDIR)\GameTime.obj"
	-@erase "$(INTDIR)\GameTime.sbr"
	-@erase "$(INTDIR)\MyFile.obj"
	-@erase "$(INTDIR)\MyFile.sbr"
	-@erase "$(INTDIR)\OwnDrawCtrl.obj"
	-@erase "$(INTDIR)\OwnDrawCtrl.sbr"
	-@erase "$(INTDIR)\Proc.obj"
	-@erase "$(INTDIR)\Proc.sbr"
	-@erase "$(INTDIR)\Stone.obj"
	-@erase "$(INTDIR)\Stone.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WeiQi.obj"
	-@erase "$(INTDIR)\WeiQi.res"
	-@erase "$(INTDIR)\WeiQi.sbr"
	-@erase "$(OUTDIR)\WeiQi.bsc"
	-@erase "$(OUTDIR)\WeiQi.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\WeiQi.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\WeiQi.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WeiQi.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\GameTime.sbr" \
	"$(INTDIR)\MyFile.sbr" \
	"$(INTDIR)\OwnDrawCtrl.sbr" \
	"$(INTDIR)\Proc.sbr" \
	"$(INTDIR)\Stone.sbr" \
	"$(INTDIR)\WeiQi.sbr"

"$(OUTDIR)\WeiQi.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Ws2_32.lib Winmm.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\WeiQi.pdb" /machine:I386 /out:"$(OUTDIR)\WeiQi.exe" 
LINK32_OBJS= \
	"$(INTDIR)\GameTime.obj" \
	"$(INTDIR)\MyFile.obj" \
	"$(INTDIR)\OwnDrawCtrl.obj" \
	"$(INTDIR)\Proc.obj" \
	"$(INTDIR)\Stone.obj" \
	"$(INTDIR)\WeiQi.obj" \
	"$(INTDIR)\WeiQi.res"

"$(OUTDIR)\WeiQi.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WeiQi - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\WeiQi.exe" "$(OUTDIR)\WeiQi.bsc"


CLEAN :
	-@erase "$(INTDIR)\GameTime.obj"
	-@erase "$(INTDIR)\GameTime.sbr"
	-@erase "$(INTDIR)\MyFile.obj"
	-@erase "$(INTDIR)\MyFile.sbr"
	-@erase "$(INTDIR)\OwnDrawCtrl.obj"
	-@erase "$(INTDIR)\OwnDrawCtrl.sbr"
	-@erase "$(INTDIR)\Proc.obj"
	-@erase "$(INTDIR)\Proc.sbr"
	-@erase "$(INTDIR)\Stone.obj"
	-@erase "$(INTDIR)\Stone.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WeiQi.obj"
	-@erase "$(INTDIR)\WeiQi.res"
	-@erase "$(INTDIR)\WeiQi.sbr"
	-@erase "$(OUTDIR)\WeiQi.bsc"
	-@erase "$(OUTDIR)\WeiQi.exe"
	-@erase "$(OUTDIR)\WeiQi.ilk"
	-@erase "$(OUTDIR)\WeiQi.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\WeiQi.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\WeiQi.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WeiQi.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\GameTime.sbr" \
	"$(INTDIR)\MyFile.sbr" \
	"$(INTDIR)\OwnDrawCtrl.sbr" \
	"$(INTDIR)\Proc.sbr" \
	"$(INTDIR)\Stone.sbr" \
	"$(INTDIR)\WeiQi.sbr"

"$(OUTDIR)\WeiQi.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=Ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Winmm.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\WeiQi.pdb" /debug /machine:I386 /out:"$(OUTDIR)\WeiQi.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\GameTime.obj" \
	"$(INTDIR)\MyFile.obj" \
	"$(INTDIR)\OwnDrawCtrl.obj" \
	"$(INTDIR)\Proc.obj" \
	"$(INTDIR)\Stone.obj" \
	"$(INTDIR)\WeiQi.obj" \
	"$(INTDIR)\WeiQi.res"

"$(OUTDIR)\WeiQi.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("WeiQi.dep")
!INCLUDE "WeiQi.dep"
!ELSE 
!MESSAGE Warning: cannot find "WeiQi.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WeiQi - Win32 Release" || "$(CFG)" == "WeiQi - Win32 Debug"
SOURCE=.\GameTime.c

"$(INTDIR)\GameTime.obj"	"$(INTDIR)\GameTime.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MyFile.c

"$(INTDIR)\MyFile.obj"	"$(INTDIR)\MyFile.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\OwnDrawCtrl.c

"$(INTDIR)\OwnDrawCtrl.obj"	"$(INTDIR)\OwnDrawCtrl.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Proc.c

"$(INTDIR)\Proc.obj"	"$(INTDIR)\Proc.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Stone.c

"$(INTDIR)\Stone.obj"	"$(INTDIR)\Stone.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\WeiQi.c

"$(INTDIR)\WeiQi.obj"	"$(INTDIR)\WeiQi.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\WeiQi.rc

"$(INTDIR)\WeiQi.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

