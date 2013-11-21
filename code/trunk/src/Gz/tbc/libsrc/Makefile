all:main
main:main.o des.a
	#cc -o main main.o md5.a -lsocket  -lx -lm -lc
	cc -q64 -o main main.o libtbc_des.a -lm -lc

main.o:main.c
	cc -q64 -c main.c

des.o:des.c 
	cc -q64 -c des.c

des.a: des.o
	ar -X64 rv libtbc_des.a des.o

clean:
	rm *.o
