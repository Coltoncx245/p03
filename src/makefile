all: bst
bst: removal main.o utility.o
	g++ -o bst main.o utility.o
main.o: main.cpp
	g++ -c -g main.cpp
utility.o: utility.cpp
	g++ -c -g utility.cpp
removal:
	rm -f *.o