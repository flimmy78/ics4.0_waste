MODULE = Gz/pft

include $(RULES_MAKEFILE)

USERINCL = $(DB2INCDIR) $(MQINCDIR)
USERLIBS = $(DB2LIBDIR) $(DB2LIBS) $(MQLIBDIR) $(MQLIBS)  -lm -lhiswcode -lbptrandata -lbponlbs -lbpdb -lhipex -lhicrc -lhirdo -lhiatlpub  -lhiafp -lhirpt -lhimon
USERFLAG = -D_HI_VARARGS -DDEBUG

DLLNAME1 = pft.so
OBJNAME1 = pft.o

ALL = $(DLLNAME1)

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1)

install:
	cp -f ../dll/pft.so  $(HOME)/app/pft/dll
	cp -f ../bnd/pft.bnd  $(HOME)/app/pft/bnd
	db2 connect to db2front
	db2 bind $(HOME)/app/pft/bnd/pft.bnd
	db2 disconnect db2front

clean:
	-rm -f *.o pft.c xx *.exp pft.sqc
