all: bst
bst: main.o utility.o 
	g++ -o bst main.o utility.o
main.o: main.cpp LazyBinarySearchTree.h
	g++ -c -g main.cpp
utility.o: utility.cpp
	g++ -c -g utility.cpp
clean:
	del -f *.o