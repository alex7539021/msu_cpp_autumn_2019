build: main.cpp BinSort.cpp BinSort.h
		g++ -std=c++11 main.cpp BinSort.cpp -pthread -o main

run: build

test: build
		./main

clean: 
		rm -f *.o main         