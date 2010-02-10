MODULE = Gz/hawa

include $(RULES_MAKEFILE)

USERINCL =
USERLIBS = -lhiurl -lhiftpcli -lhiftpsvr -lhipra -lbpbase -lbpdb -lbpdebug -lbponlbs -lbptrandata -lhicrc -lhirdo -lhisaf -lsqnmng -lhipex -lhiafp -lhiatlpub -lhidba -lhimon -lhirpt

USERFLAG =

DLLNAME1 = pre_haw.so
OBJNAME1 = pre_haw.o

ALL = $(DLLNAME1)

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1)

install:
	cp -f ../dll/pre_haw.so  $(HOME)/app/hawa/dll

clean:
	-rm *.o *.exp
