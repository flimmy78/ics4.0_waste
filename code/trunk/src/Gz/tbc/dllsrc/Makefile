MODULE		= Gz/tbc

include $(RULES_MAKEFILE)

USERINCL = $(DB2INCDIR)
USERLIBS = -bloadmap:xx -lmd5 -lbptrandata -lhibase -lbponlbs -lbpdb -lhipex -lhicrc -lhirdo -lhiafp -lhimon -lsqnmng -lhiatlpub -lpthread -lm $(DB2LIBDIR) $(DB2LIBS)

USERFLAG	= -D_HI_VARARGS -DDEBUG

DLLNAME1	= tbc.so
OBJNAME1	= tbc.cp

ALL		= $(DLLNAME1) 

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1) 

install:
	cp -f ../dll/tbc.so  $(HOME)/app/tbc/dll
	cp -f ../bnd/tbc.bnd  $(HOME)/app/tbc/bnd

	db2 connect to db2front
	db2 bind $(HOME)/app/tbc/bnd/tbc.bnd
	db2 disconnect db2front

clean:
	-rm *.o *.c  xx *.exp *.sqc
