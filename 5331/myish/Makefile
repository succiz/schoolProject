###########################################################
#
# Simple Makefile for Operating Systems Project 1
# myish
#
###########################################################
.SUFFIXES: .h .c .cpp .l .o

myish: myish.yy.o myish.o
	g++ myish.yy.o myish.o -o myish -lfl

myish.o: myish.cpp
	g++ -c myish.cpp

myish.yy.o: myish.yy.c
	gcc -c myish.yy.c

myish.yy.c: myish.l
	flex -omyish.yy.c myish.l

clean:
	/bin/rm -f *.o *~ core myish myish.yy.c



