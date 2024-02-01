CXX = g++
# CXXFLAGS = -Wall
OBJ = arvoreBB.o vetorOrdenado.o treap.o arvore23.o arvoreRN.o


all: $(OBJ)
	$(CXX) -o ep1 ep1.cpp $(OBJ)

arvoreBB.o: arvoreBB.cpp arvoreBB.h
	$(CXX) -c -o $@ $<

vetorOrdenado.o: vetorOrdenado.cpp vetorOrdenado.h
	$(CXX) -c -o $@ $<

treap.o: treap.cpp treap.h
	$(CXX) -c -o $@ $<

arvore23.o: arvore23.cpp arvore23.h
	$(CXX) -c -o $@ $<

arvoreRN.o: arvoreRN.cpp arvoreRN.h
	$(CXX) -c -o $@ $<

clean:
	@rm -rf *.o html