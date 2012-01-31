CC=gcc
CFLAGS=-posix -pedantic -Wall
CFLAGS+=-I/usr/include -L/usr/lib64 -lbsd

all:
	${CC} ${CFLAGS} -g -o peli peli.c slist.c 
