all: p03
p03: main.o utility.o 
	g++ -o p03 main.o utility.o
main.o: main.cpp LazyBinarySearchTree.h
	g++ -c -g main.cpp
utility.o: utility.cpp
	g++ -c -g utility.cpp
clean:
	rm -f *.o p03.exe