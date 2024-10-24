all: p03
p03: main.o lbst.o utility.o 
	g++ -o p03 main.o LazyBinarySearchTree.o utility.o 
main.o: main.cpp lbst.o
	g++ -c -g main.cpp
lbst.o: LazyBinarySearchTree.cpp 
	g++ -c -g LazyBinarySearchTree.cpp
utility.o: utility.cpp
	g++ -c -g utility.cpp
clean:
	rm -f *.o p03.exe