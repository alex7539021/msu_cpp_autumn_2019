build: tests.cpp BigInt.cpp BigInt.h
		g++-6 tests.cpp BigInt.cpp -o tests

run: build

test: build
		./tests

valgrind: build
		valgrind --track-origins=yes ./tests

clean: 
		rm -f *.o tests
