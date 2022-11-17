# eenvoudige makefile
all: hoofd.o othellobord.o
	g++ -Wall -o hetspel othellobord.o hoofd.o
othellobord.o: othellobord.cc othellobord.h
	g++ -Wall -c othellobord.cc
hoofd.o: hoofd.cc othellobord.h
	g++ -Wall -c hoofd.cc
