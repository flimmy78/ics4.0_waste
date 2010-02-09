MODULE		= Gz/rtya

include $(RULES_MAKEFILE)

USERINCL = $(DB2INCDIR)
USERLIBS = -bloadmap:xx -lbptrandata -lhibase -lbponlbs -lbpdb -lhipex  -lhicrc -lhirdo  -lhiafp -lhimon -lhiatlpub -lsqnmng -lmd5  $(DB2LIBDIR) $(DB2LIBS)

USERFLAG	= -D_HI_VARARGS -DDEBUG

DLLNAME1	= rty.so
OBJNAME1	= rty.cp
#OBJNAME1	= rty.o

ALL		= $(DLLNAME1) 

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1) 

install:
	cp -f ../dll/rty.so  $(HOME)/app/rtya/dll
	cp -f ../bnd/rty.bnd  $(HOME)/app/rtya/bnd

	db2 connect to db2front
	db2 bind $(HOME)/app/rtya/bnd/rty.bnd
	db2 disconnect db2front

clean:
	-rm *.o  xx  *.sqc
