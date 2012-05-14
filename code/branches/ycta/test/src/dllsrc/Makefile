MODULE		= Gz/efea

include $(RULES_MAKEFILE)

USERLIBS = -lhiipchk  -lcfgrs
USERFLAG = -DDEBUG

DLLNAME1 = ecncliasyncl2_gzdl.so
DLLOBJS1 = ecncliasyncl2_gzdl.o 

DLLNAME2 = ecnsvrasyncl2_gzdl.so
DLLOBJS2 = ecnsvrasyncl2_gzdl.o

ALL =  $(DLLNAME1) $(DLLNAME2) 

all: $(ALL)

$(DLLNAME1): $(DLLOBJS1)
$(DLLNAME2): $(DLLOBJS2)


clean:
	-rm *.o *.exp
	
