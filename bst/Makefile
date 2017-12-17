all: bst test
	echo "Created bst and test files."

bst:
	gcc -c bst.c bst.h

test: bst
	gcc -o bst_test bst_test.c bst.o

run-test: test
	valgrind ./bst_test

clean:
	-rm *.o
	-rm *.gch
	-rm bst_test
