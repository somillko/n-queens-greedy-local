all: n_queens_greedy

n_queens_greedy: n_queens_greedy.o
	g++ -O2 --std=c++11 n_queens_greedy.o -o n_queens_greedy

n_queens_greedy.o: n_queens_greedy.cpp
	g++ -O2 --std=c++11 -c n_queens_greedy.cpp

clean:
	rm n_queens_greedy
	rm n_queens_greedy.o
