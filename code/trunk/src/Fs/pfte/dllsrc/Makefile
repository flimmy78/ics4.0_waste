DEVDIR   = /app/ics/src
MODULE		= Fs/pfte

include $(RULES_MAKEFILE)

USERLIBS	= -bloadmap:xx -lbptrandata -lhibase -lbponlbs -lhidbt -lbpdb -lhipex -lhidbpool -lhicrc -lhirdo -lhidbbase -lhiafp -lhimon -lhiatlpub -lsqnmng

USERFLAG	= -D_HI_VARARGS -DDEBUG

DLLNAME1	= pft_446.so
OBJNAME1	= pft_446.cp

ALL		= $(DLLNAME1) 

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1) 

install:
	cp -f ../dll/pft_446.so  $(HOME)/dll
	cp -f ../bnd/pft_446.bnd  $(HOME)/bnd

	db2 connect to db2front
	db2 bind $(HOME)/bnd/pft.bnd
	db2 disconnect db2front

clean:
#	-rm *.o *.c xx *.exp *.sqc
	-rm *.o xx *.sqc
