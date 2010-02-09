.SUFFIXES: .c .o

CC=cc
NOLINK= -c -g -DDEBUG
LIBDIR=$(HOME)/src/Gz/cbs/lib

OBJS = Cbs8583.o Gb2132.o Errlog.o Trace.o

all: lib

lib: libCbs.a clean

libCbs.a: $(OBJS)
	@echo Compliling the program $@
	ar -rv $@ `lorder $(OBJS) | tsort`
	@mv $@ $(LIBDIR)
	@echo $@ is now up-to-date

.c.o:
	@echo Compiling $<
	$(CC) $(NOLINK) $<

clean:
	-rm *.o
