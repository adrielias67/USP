CXX = g++
# CXXFLAGS = -Wall
OBJ = palavra.o grafo.o


all: $(OBJ)
	$(CXX) -o ep3 ep3.cpp $(OBJ)

palavra.o: palavra.cpp palavra.h
	$(CXX) -c -o $@ $<

grafo.o: grafo.cpp grafo.h
	$(CXX) -c -o $@ $<

clean:
	@rm -rf *.o html