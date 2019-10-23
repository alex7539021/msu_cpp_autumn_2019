build: tests.cpp LinearAllocator.cpp LinearAllocator.h
		g++-6 tests.cpp LinearAllocator.cpp -o tests

run: build
		./tests RUN

test: build
		./tests TEST

clean: 
		rm -f *.o tests