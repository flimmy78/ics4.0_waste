MODULE = Gz/ssaa

include $(RULES_MAKEFILE)

USERLIBS	= -lbptrandata -lhibase -lbponlbs -lbpdb -lhipex -lhicrc -lhirdo -lhisaf -lhiafp -lhimon
USERFLAG	= -D_HI_VARARGS -DDEBUG

DLLNAME1	= gzsb_pre.so
OBJNAME1	= gzsb_pre.o

ALL		= $(DLLNAME1) 

all: $(ALL) clean

$(DLLNAME1): $(OBJNAME1) 


clean:
	-rm *.o  *.exp 
