all: hashmap test
    echo "Created hashmap and test files."

hashmap:
    gcc -c hashmap.c hashmap.h

test: hashmap
    gcc -g -o hashmap_test hashmap_test.c hashmap.o

run-test: test
    valgrind ./hashmap_test

clean:
    -rm *.o
    -rm *.gch
    -rm hashmap_test
