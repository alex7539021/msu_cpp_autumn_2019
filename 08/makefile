build: tests.cpp ThreadPool.h
		g++ -std=c++11 tests.cpp -pthread -o tests

run: build

test: build
		./tests

valgrind: build
		valgrind --track-origins=yes ./tests

clean: 
		rm -f *.o tests
