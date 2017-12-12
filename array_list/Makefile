all: array-list test
	echo "Created array list and test files."

array-list:
	gcc -c array_list.c array_list.h

test: array-list
	gcc -o array_list_test array_list_test.c array_list.o

run-test: test
	valgrind ./array_list_test

clean:
	-rm *.o
	-rm *.gch
	-rm array_list_test
