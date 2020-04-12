################################################################
# Names: Ron Landagan, cssc1917 (Team Lead), 
#        Wiliton Rogdrigues, cssc1922 (Developer),
#        Joshua Vargas, cssc1973 (Developer),
#        Isaiah Dorado, cssc1929 (Developer)
# Username: cssc1917
# Project: CS530 Assignment 2
# File: makefile
# Notes: This is the makefile that compiles the assignment2.cpp 
#        file.
################################################################

EXEC = dxe
CC = g++
CFLIGS = -I.

$(EXEC):
	$(CC) -o $(EXEC) assignment2.cpp -std=c++11
	rm -f *.o

clean:
	rm -f *.o core a.out $(EXEC) 

########################[ EOF: Makefile ]#######################
