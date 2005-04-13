# Microsoft Developer Studio Generated NMAKE File, Based on texturegenerator.dsp
!IF "$(CFG)" == ""
CFG=texturegenerator - Win32 Debug
!MESSAGE No configuration specified. Defaulting to texturegenerator - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "texturegenerator - Win32 Release" && "$(CFG)" != "texturegenerator - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "texturegenerator.mak" CFG="texturegenerator - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "texturegenerator - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "texturegenerator - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "texturegenerator - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\texturegenerator.exe"

!ELSE 

ALL : "cactus - Win32 Release" "$(OUTDIR)\texturegenerator.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cactus - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\texturegenerator.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\texturegenerator.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D "__WXMSW__" /D DEBUG=1 /D "__WIN32__" /D WINVER=0x0400 /D "wxUSE_DYNAMIC_LOADER" /Fp"$(INTDIR)\texturegenerator.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\texturegenerator.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wx.lib comctl32.lib wsock32.lib jpeg.lib ../lib/cactus.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\texturegenerator.pdb" /machine:I386 /out:"$(OUTDIR)\texturegenerator.exe" 
LINK32_OBJS= \
	"$(INTDIR)\texturegenerator.obj" \
	"..\lib\cactus.lib"

"$(OUTDIR)\texturegenerator.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "texturegenerator - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\texturegenerator.exe"

!ELSE 

ALL : "cactus - Win32 Debug" "$(OUTDIR)\texturegenerator.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cactus - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\texturegenerator.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\texturegenerator.exe"
	-@erase "$(OUTDIR)\texturegenerator.ilk"
	-@erase "$(OUTDIR)\texturegenerator.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D "__WXMSW__" /D DEBUG=1 /D "__WIN32__" /D WINVER=0x0400 /D "wxUSE_DYNAMIC_LOADER" /Fp"$(INTDIR)\texturegenerator.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\texturegenerator.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wx.lib comctl32.lib wsock32.lib jpeg.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\texturegenerator.pdb" /debug /machine:I386 /nodefaultlib:"libcd.lib" /out:"$(OUTDIR)\texturegenerator.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\texturegenerator.obj" \
	"..\lib\cactusd.lib"

"$(OUTDIR)\texturegenerator.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("texturegenerator.dep")
!INCLUDE "texturegenerator.dep"
!ELSE 
!MESSAGE Warning: cannot find "texturegenerator.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "texturegenerator - Win32 Release" || "$(CFG)" == "texturegenerator - Win32 Debug"
SOURCE=.\texturegenerator.cpp

"$(INTDIR)\texturegenerator.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "texturegenerator - Win32 Release"

"cactus - Win32 Release" : 
   cd "\cactus"
   $(MAKE) /$(MAKEFLAGS) /F .\cactus.mak CFG="cactus - Win32 Release" 
   cd ".\texturegenerator"

"cactus - Win32 ReleaseCLEAN" : 
   cd "\cactus"
   $(MAKE) /$(MAKEFLAGS) /F .\cactus.mak CFG="cactus - Win32 Release" RECURSE=1 CLEAN 
   cd ".\texturegenerator"

!ELSEIF  "$(CFG)" == "texturegenerator - Win32 Debug"

"cactus - Win32 Debug" : 
   cd "\cactus"
   $(MAKE) /$(MAKEFLAGS) /F .\cactus.mak CFG="cactus - Win32 Debug" 
   cd ".\texturegenerator"

"cactus - Win32 DebugCLEAN" : 
   cd "\cactus"
   $(MAKE) /$(MAKEFLAGS) /F .\cactus.mak CFG="cactus - Win32 Debug" RECURSE=1 CLEAN 
   cd ".\texturegenerator"

!ENDIF 


!ENDIF 

