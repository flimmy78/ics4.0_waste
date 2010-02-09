DEVDIR = /app/ics/src
MODULE = Gz/pfa

include $(RULES_MAKEFILE)

USERLIBS = -bloadmap:xx -lbptrandata -lhibase -lbponlbs -lhidbt -lbpdb -lhipex -lhidbpool -lhicrc -lhirdo -lhidbbase -lhiafp -lhimon -lmsgfmt -lbufcvt -lhiatlpub -lsqnmng

USERFLAG	= -D_HI_VARARGS -DDEBUG

DLLNAME1	= pfa.so
OBJNAME1	= pfa.cp

ALL		= $(DLLNAME1) 

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1) 

install:
	cp -f ../dll/pfa.so  $(HOME)/dll
	cp -f ../bnd/pfa.bnd  $(HOME)/bnd

	db2 connect to db2front
	db2 bind $(HOME)/bnd/pfa.bnd
	db2 disconnect db2front

clean:
	-rm *.o *.c  xx *.exp *.sqc
