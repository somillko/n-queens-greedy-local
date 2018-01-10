all: n-queens-greedy

n-queens-greedy: n-queens-greedy.o
	g++ -O2 --std=c++11 n-queens-greedy.o -o n-queens-greedy

n-queens-greedy.o: n-queens-greedy.cpp
	g++ -O2 --std=c++11 -c n-queens-greedy.cpp

clean:
	rm n-queens-greedy
	rm n-queens-greedy.o
