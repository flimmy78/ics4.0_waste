MODULE = Gz/cbs

include $(RULES_MAKEFILE)

USERINCL = $(DB2INCDIR) $(MQINCDIR)
USERLIBS = $(DB2LIBDIR) $(DB2LIBS) $(MQLIBDIR) $(MQLIBS)  -lm -lhiswcode -lbptrandata -lbponlbs -lbpdb -lhipex -lhicrc -lhirdo -lhiatlpub  -lhiafp -lhirpt -lhimon -lCbs
USERFLAG = -D_HI_VARARGS -DDEBUG

DLLNAME1 = cbs.so
OBJNAME1 = cbs.cp

ALL = $(DLLNAME1)

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1)

install:
	cp -f ../dll/cbs.so  $(HOME)/app/cbs/dll
	cp -f ../bnd/cbs.bnd  $(HOME)/app/cbs/bnd
	db2 connect to db2front
	db2 bind $(HOME)/app/cbs/bnd/cbs.bnd
	db2 disconnect db2front

clean:
	-rm -f *.o xx *.exp cbs.sqc
