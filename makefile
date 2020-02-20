all: randmst

randmst: randmst.cpp
	g++ -Wall -g -o  randmst randmst.cpp

clean:
	rm -f randmst