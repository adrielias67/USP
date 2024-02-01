#!/bin/bash -x                                                                  

function check {
	if [ "$?" -ne 0 ]; then
		echo "Erro na compilação! Abortando o processo"
		exit 1
	fi
}

rm -f propriedadesnumericas.a libvetoraleatorio.so

# compilação da biblioteca  estática propriedadesnumericas.h
gcc -Wall -c -o propriedadesnumericas.o propriedadesnumericas.c
check
ar -rcv libpropriedadesnumericas.a propriedadesnumericas.o

# compilação da biblioteca  estática vetoraleatorio.h
gcc -c -fPIC -o vetoraleatorio.o vetoraleatorio.c
check
gcc -o libvetoraleatorio.so -shared vetoraleatorio.o
# a biblioteca é salva em /tmp:
mv libvetoraleatorio.so /tmp
gcc -Wall -o testa testa.c -L/tmp -lvetoraleatorio libpropriedadesnumericas.a
check
export LD_LIBRARY_PATH=/tmp

# geração do doxygen
doxygen Doxyfile
check

rm -f propriedadesnumericas.o vetoraleatorio.o

# teste das bibliotecas
./testa

exit 0

