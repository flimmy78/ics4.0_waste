all:main
main:main.o md5.a
	#cc -o main main.o md5.a -lsocket  -lx -lm -lc
	cc -o main main.o md5.a -lm -lc

main.o:main.c
	cc -c main.c

mddrvier1.o:mddriver1.c global.h
	cc -c mddriver1.c

md5c.o:md5c.c md5.h global.h
	cc -c md5c.c

md5.a:mddriver1.o md5c.o global.h
	ar rv md5.a mddriver1.o md5c.o

clean:
	rm *.o
