MODULE		= Gz/tbc

include $(RULES_MAKEFILE)

USERINCL = 
USERLIBS    =   -lhiurl -lhiftpcli -lhiftpsvr -lhipra -lbpbase -lbpdb -lbpdebug -lbponlbs -lbptrandata -lhicrc -lhirdo -lhisaf -lsqnmng -lhipex -lhiafp -lhiatlpub -lhidba -lhimon -lhirpt  -ltbc_des
USERFLAG    = 

DLLNAME1 = pre_tbc.so
OBJNAME1 = pre_tbc.c

ALL = $(DLLNAME1)

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1)

install:
	cp -f ../dll/pre_tbc.so  $(HOME)/app/tbc/dll

clean:
	-rm *.exp *.o
