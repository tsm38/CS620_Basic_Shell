#
# Makefile for myshell tests
#

CC = gcc
CFLAGS = -g -Wall -std=gnu99
EXES = myshell myhistory 

all: myshell myhistory





myshell: myshell.o 
	gcc -o myshell myshell.o 

myhistory: myhistory.o 
	gcc -o myhistory myhistory.o  

myshell.o: myshell.c myshell.h
	gcc -c myshell.c

myhistory.o: myhistory.c myhistory.h 
	gcc -c myhistory.c

clean:
	-rm -f *.o $(EXES)

