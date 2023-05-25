.AUTODEPEND

.PATH.obj = ..\

#		*Translator Definitions*
CC = bcc +TANQUES.CFG
TASM = TASM
TLIB = tlib
TLINK = tlink
LIBPATH = C:\PROG\BORLANDC\LIB
INCLUDEPATH = C:\PROG\BORLANDC\INCLUDE


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
 tanques.obj \
 batalla.obj \
 video.obj \
 ..\serie.obj \
 ..\sonido.obj \
 teclado.obj

#		*Explicit Rules*
..\tanques.exe: tanques.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/L$(LIBPATH) @&&|
c0h.obj+
..\\tanques.obj+
..\\batalla.obj+
..\\video.obj+
..\serie.obj+
..\sonido.obj+
..\\teclado.obj
..\tanques
		# no map file
emu.lib+
mathh.lib+
ch.lib
|


#		*Individual File Dependencies*
tanques.obj: tanques.cfg tanques.c 

batalla.obj: tanques.cfg batalla.c 

video.obj: tanques.cfg video.c 

..\serie.obj: tanques.cfg serie.c 

..\sonido.obj: tanques.cfg sonido.c 

teclado.obj: tanques.cfg teclado.c 

#		*Compiler Configuration File*
tanques.cfg: tanques.mak
  copy &&|
-mh
-3
-v
-G
-O
-Og
-Oe
-Om
-Ov
-Ol
-Ob
-Op
-Oi
-Z
-k-
-vi-
-weas
-wpre
-n..\
-I$(INCLUDEPATH)
-L$(LIBPATH)
| tanques.cfg


