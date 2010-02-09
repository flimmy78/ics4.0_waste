.SUFFIXES: .c .o

CC=cc
NOLINK= -c -g -DDEBUG
LIBDIR=$(HOME)/src/Gz/hawa/lib

OBJS = md5c.o mddriver1.o

all: lib

lib: libMd5.a clean

libMd5.a: $(OBJS)
	@echo Compliling the program $@
	ar -rv $@ `lorder $(OBJS) | tsort`
	@mv $@ $(LIBDIR)
	@echo $@ is now up-to-date

.c.o:
	@echo Compiling $<
	$(CC) $(NOLINK) $<

clean:
	-rm *.o
