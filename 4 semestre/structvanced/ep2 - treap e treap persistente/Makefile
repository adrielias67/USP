CXX = g++
# CXXFLAGS = -Wall
OBJ = treap.o treapF.o


all: $(OBJ)
	$(CXX) -o main main.cpp $(OBJ)

treap.o: treap.cpp treap.h
	$(CXX) -c -o $@ $<

treapF.o: treapF.cpp treapF.h
	$(CXX) -c -o $@ $<

clean:
	@rm -rf *.o html