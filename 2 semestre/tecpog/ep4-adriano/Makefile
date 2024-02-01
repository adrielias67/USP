CXX = g++
# CXXFLAGS = -Wall
OBJ = Arquivo.o Fantasma.o Labirinto.o Pacman.o Partida.o Personagem.o


all: $(OBJ)
	$(CXX) -o ep4 ep4.cpp $(OBJ)

Arquivo.o: Arquivo.cpp Arquivo.h
	$(CXX) -c -o $@ $<

Fantasma.o: Fantasma.cpp Fantasma.h
	$(CXX) -c -o $@ $<

Labitinto.o: Labitinto.cpp Labitinto.h
	$(CXX) -c -o $@ $<

Pacman.o: Pacman.cpp Pacman.h
	$(CXX) -c -o $@ $<

Partida.o: Partida.cpp Partida.h
	$(CXX) -c -o $@ $<

Personagem.o: Personagem.cpp Personagem.h
	$(CXX) -c -o $@ $<


clean:
	@rm -rf *.o html