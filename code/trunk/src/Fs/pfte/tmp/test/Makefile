MODULE		= Fs/pfte

include $(RULES_MAKEFILE)

USERLIBS	= -lhidbbase -lets
USERFLAG	= -D_HI_VARARGS -DDEBUG

#EXENAME1	= test
#OBJNAME1	= test.o

EXENAME1	= t
OBJNAME1	= t.o


ALL			= $(EXENAME1)

all: $(ALL) clean

$(EXENAME1): $(OBJNAME1)
	$(CC) $(EXFLAGS) $(CPFLAGS) -o $(PRIBINDIR)/$@ $? ../../lib/sftp_lzari.o ../../lib/rtsb_file_mac.a ../../lib/libets.a

clean:
	-rm t.c *.o *.exp *.sqc

