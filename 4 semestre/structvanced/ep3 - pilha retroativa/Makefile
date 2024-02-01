CXX = g++
#CXXFLAGS = -Wall -g
OBJ = pilhaR.o treap.o


all: $(OBJ)
	$(CXX) -o main main.cpp $(OBJ) 2> /dev/null

pilhaR.o: pilhaR.cpp pilhaR.h
	$(CXX) -c -o $@ $< 2> /dev/null

treap.o: treap.cpp treap.h
	$(CXX) -c -o $@ $< 2> /dev/null

clean:
	@rm -rf *.o html