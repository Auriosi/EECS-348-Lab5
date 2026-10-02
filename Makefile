CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

main: matrix.o main.o
	$(CXX) $(CXXFLAGS) matrix.cpp main.cpp -o main

clean:
	rm -rf *.o
	rm -f main