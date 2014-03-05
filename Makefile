# Author : Vinayak Bhargav Srinath 
# the Makefile pools in for two problems as of now, will add more once its done

test: problem1.o problem2.o functions.o  
	gcc -o problem1 problem1.o functions.o
	gcc -o problem2 problem2.o functions.o

part1.o: functions.c functions.h
	gcc -O -c functions.c

problem1.o: problem1.c
	gcc -O -c problem1.c 

problem2.o: problem2.c
	gcc -O -c problem2.c 

clean:
	rm -rf problem1 problem2 *.o

