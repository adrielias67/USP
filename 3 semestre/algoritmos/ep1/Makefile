CXX = g++
# CXXFLAGS = -Wall
OBJ = arvoreBB.o vetorOrdenado.o


all: $(OBJ)
	$(CXX) -o ep1 ep1.cpp $(OBJ) 

arvoreBB.o: arvoreBB.cpp arvoreBB.h
	$(CXX) -c -o $@ $<
	
vetorOrdenado.o: vetorOrdenado.cpp vetorOrdenado.h
	$(CXX) -c -o $@ $<

clean:
	@rm -rf *.o html