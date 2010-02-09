MODULE = Gz/hawa

include $(RULES_MAKEFILE)

USERINCL = $(DB2INCDIR) $(MQINCDIR)
USERLIBS = $(DB2LIBDIR) $(DB2LIBS) $(MQLIBDIR) $(MQLIBS)  -lm -lhiswcode -lbptrandata -lbponlbs -lbpdb -lhipex -lhicrc -lhirdo -lhiatlpub  -lhiafp -lhirpt -lhimon
USERFLAG = -D_HI_VARARGS -DDEBUG

DLLNAME1 = hawa.so
OBJNAME1 = hawa.o

ALL = $(DLLNAME1)

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1)

install:
	cp -f ../dll/hawa.so  $(HOME)/app/hawa/dll

clean:
	-rm -f *.o hawa.c xx *.exp hawa.sqc
