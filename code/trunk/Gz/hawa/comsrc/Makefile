MODULE = Gz/hawa

include $(RULES_MAKEFILE)

USERINCL = $(DB2INCDIR) $(MQINCDIR)
USERLIBS = $(DB2LIBDIR) $(DB2LIBS) $(MQLIBDIR) $(MQLIBS) -lm -lhiswcode -lbptrandata -lbponlbs -lbpdb -lhipex -lhicrc -lhirdo -lhiatlpub -lhiafp -lhirpt -lhimon

USERFLAG = -D_HI_VARARGS

DLLNAME1 = pre_haw.so
OBJNAME1 = pre_haw.c

ALL = $(DLLNAME1)

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1)

install:
	cp -f ../dll/pre_haw.so  $(HOME)/app/hawa/dll

clean:
	-rm *.o *.exp
