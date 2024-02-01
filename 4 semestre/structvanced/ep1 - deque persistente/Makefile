CXX = g++
# CXXFLAGS = -Wall
OBJ = deque.o


all: $(OBJ)
	$(CXX) -o main main.cpp $(OBJ)

deque.o: deque.cpp deque.h
	$(CXX) -c -o $@ $<

clean:
	@rm -rf *.o html