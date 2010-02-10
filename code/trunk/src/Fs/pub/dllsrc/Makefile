MODULE		= Fs/pub

include $(RULES_MAKEFILE)

USERLIBS	= -lhiafp -lhipex -lhiswcode
USERFLAG	= 

DLLNAME1 = fs_pre.so
DLLOBJS1 = fs_pre.c

ALL = $(DLLNAME1)
all: $(ALL) clean cpdll

$(DLLNAME1): $(DLLOBJS1)

clean:
	-rm *.o

cpdll:
	-cp -f ../dll/fs_pre.so /app/ics/dll
