CXX = g++
# CXXFLAGS = -Wall
OBJ = grafo.o


all: $(OBJ)
	$(CXX) -o ep4 ep4.cpp $(OBJ)

grafo.o: grafo.cpp grafo.h
	$(CXX) -c -o $@ $<

clean:
	@rm -rf *.o html