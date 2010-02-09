MODULE		= Gz/lshf

include $(RULES_MAKEFILE)

USERINCL = $(DB2INCDIR)
USERLIBS = -bloadmap:xx -lmqclient -lbptrandata -lhibase -lbponlbs -lbpdb -lhipex -lhicrc -lhirdo -lhiafp -lhimon -lsqnmng -lhiatlpub -lpthread -lm $(DB2LIBDIR) $(DB2LIBS)

USERFLAG	= -D_HI_VARARGS -DDEBUG

DLLNAME1	= mq.so
OBJNAME1	= mq.cp

ALL		= $(DLLNAME1) 

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1) 

install:
	cp -f ../dll/mq.so  $(HOME)/app/lshf/dll
	cp -f ../bnd/mq.bnd  $(HOME)/app/lshf/bnd

clean:
	-rm *.o *.c  xx *.exp *.sqc
