MODULE		= Gz/pft

include $(RULES_MAKEFILE)

USERLIBS	= -lhidbbase -lets
USERFLAG	= -D_HI_VARARGS -DDEBUG

EXENAME1	= encsvr_pft
OBJNAME1	= encsvr_pft.o 

ALL			= $(EXENAME1)

all: $(ALL) clean

$(EXENAME1): $(OBJNAME1)
	$(CC) $(EXFLAGS) $(CPFLAGS) -o $(PRIBINDIR)/$@ $? ../lib/sftp_lzari.o

clean:
	-rm encsvr_pft.c *.o *.exp *.sqc

