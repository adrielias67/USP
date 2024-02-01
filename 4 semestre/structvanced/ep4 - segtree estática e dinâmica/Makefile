CXX = g++
CXXFLAGS = -Wall
OBJ = as.o asd.o


all: $(OBJ)
	$(CXX) -o main main.cpp $(OBJ) $(CXXFLAGS) 2> /dev/null

as.o: as.cpp as.h
	$(CXX) -c -o $@ $<

asd.o: asd.cpp asd.h
	$(CXX) -c -o $@ $<

clean:
	@rm -rf *.o html