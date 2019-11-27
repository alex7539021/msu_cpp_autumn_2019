build: tests.cpp vector.h
		g++-6 tests.cpp -o tests

run: build

test: build
		./tests

valgrind: build
		valgrind --track-origins=yes ./tests

clean: 
		rm -f *.o tests
