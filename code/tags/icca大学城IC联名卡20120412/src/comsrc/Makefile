MODULE		= Gz/icca

include $(RULES_MAKEFILE)

USERINCL = 
USERLIBS    =   -lhiurl -lhiftpcli -lhiftpsvr -lhipra -lbpbase -lbpdb -lbpdebug -lbponlbs -lbptrandata -lhicrc -lhirdo -lhisaf -lsqnmng -lhipex -lhiafp -lhiatlpub -lhidba -lhimon -lhirpt -lmd5 -llshk_des
USERFLAG    = 

DLLNAME1 = pre_icca.so
OBJNAME1 = pre_icca.c

ALL = $(DLLNAME1)

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1)

install:
	cp -f ../dll/pre_icca.so  $(HOME)/app/icca/dll

clean:
	-rm *.exp *.o
