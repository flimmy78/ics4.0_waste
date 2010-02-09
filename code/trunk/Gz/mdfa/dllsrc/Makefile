MODULE = Gz/mdfa

include $(RULES_MAKEFILE)

USERINCL = $(DB2INCDIR) $(MQINCDIR)
USERLIBS = $(DB2LIBDIR) $(DB2LIBS) $(MQLIBDIR) $(MQLIBS)  -lm -lhiswcode -lbptrandata -lbponlbs -lbpdb -lhipex -lhicrc -lhirdo -lhiatlpub  -lhiafp -lhirpt -lhimon
USERFLAG = -D_HI_VARARGS -DDEBUG

DLLNAME1 = mdfa.so
OBJNAME1 = mdfa.o

ALL = $(DLLNAME1)

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1)

install:
	cp -f ../dll/mdfa.so  $(HOME)/app/mdfa/dll
	cp -f ../bnd/mdfa.bnd  $(HOME)/app/mdfa/bnd
	db2 connect to db2front
	db2 bind $(HOME)/app/mdfa/bnd/mdfa.bnd
	db2 disconnect db2front

clean:
	-rm -f *.o mdfa.c xx *.exp mdfa.sqc
