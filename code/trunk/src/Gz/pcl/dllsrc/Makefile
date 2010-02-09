MODULE = Gz/pcl

include $(RULES_MAKEFILE)

USERINCL = $(DB2INCDIR) $(MQINCDIR)
USERLIBS = $(DB2LIBDIR) $(DB2LIBS) $(MQLIBDIR) $(MQLIBS)  -lm -lhiswcode -lbptrandata -lbponlbs -lbpdb -lhipex -lhicrc -lhirdo -lhiatlpub  -lhiafp -lhirpt -lhimon
USERFLAG = -D_HI_VARARGS -DDEBUG

DLLNAME1 = pcl.so
OBJNAME1 = pcl.o

ALL = $(DLLNAME1)

all: $(ALL) install clean

$(DLLNAME1): $(OBJNAME1)

install:
	cp -f ../dll/pcl.so  $(HOME)/app/pcl/dll
	cp -f ../bnd/pcl.bnd  $(HOME)/app/pcl/bnd
	db2 connect to db2front
	db2 bind $(HOME)/app/pcl/bnd/pcl.bnd
	db2 disconnect db2front

clean:
	-rm -f *.o pcl.c xx *.exp pcl.sqc
