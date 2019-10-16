calc: main.cpp
		g++ -std=c++1z main.cpp -o calc

run: calc
		./calc $(args)

test: calc
		python3 ./test.py

clean: 
		rm -f *.o calc