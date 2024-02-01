#pragma once

#include<iostream>


/* Key */
typedef std::string Key;


/* Item */
struct item{
    //dados de um item
    int nOcorrencias;
    int nLetras;
    int nVogais;
    
    //construtor - cria um item "nulo"
    item(){
        nOcorrencias = 0;
        nLetras = 0;
        nVogais = 0;
    }
    
    //inicializador - inicializa um item a partir da palavra dada
    item inicializa(Key key){
        item novo;

        novo.nOcorrencias = 1;
        novo.nLetras = key.length();
        for(int i=0; i<novo.nLetras; i++){
            if(key[i]=='a' || key[i]=='e' || key[i]=='i' || key[i]=='o' || key[i]=='u') novo.nVogais++;
        }

        return novo;
    }
    
    //verifica se uma palavra não tem letras repetidas. retorna true se não repete letras, e false se repete alguma
    bool verificaSR(Key palavra, int tamanho){
        int i, j;
        for(i=0; i<tamanho; i++){
            j=i+1;
            while(j<tamanho){
                if(palavra[j] == palavra[i]) return false;
                j++;
            }
        }
        return true;
    }

    //returna o número de vogais diferentes em uma palavra
    int nVD(Key palavra, int tamanho){
        int i;
        int vogais[5] = {0,0,0,0,0};
        
        for(i=0; i<tamanho; i++){
            if(palavra[i]=='a') vogais[0] = 1;
            if(palavra[i]=='e') vogais[1] = 1;
            if(palavra[i]=='i') vogais[2] = 1;
            if(palavra[i]=='o') vogais[3] = 1;
            if(palavra[i]=='u') vogais[4] = 1;
        }

        int S=0;
        for(i=0; i<5; i++){
            S += vogais[i];
        }
        
        return S;
    }
};