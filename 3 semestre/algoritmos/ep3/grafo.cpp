#include <iostream>
#include "grafo.h"
#include <fstream>
#include <algorithm>

using namespace std;



grafo::grafo(string vetorFragmentos[], int vertices){
    nVertices = vertices;
    adj = new vector<pair<int,int>> [nVertices];
    fragmentos = new string[nVertices];
    rep = new int[nVertices];

    for(int i=0; i<nVertices; i++){
        rep[i] = i;
        fragmentos[i] = vetorFragmentos[i];
    }
}


grafo::~grafo(){

}


vector<aresta> montaListaAdj(string filename){
    // Retorna a lista de adjacência, ordenada de maior a menor peso.
    int u, v, peso, nArestas;
    vector<aresta> lista;
    fstream file(filename);
    
    file >> nArestas;
    for(int i=0; i<nArestas; i++){
        file >> u >> v >> peso;
        lista.push_back(make_pair(peso, make_pair(u, v)));
    }

    file.close();

    sort(lista.begin(), lista.end());
    reverse(lista.begin(), lista.end());
    
    return lista;
}


bool corrigeRep(int u, int pai, int rep[], vector<pair<int,int>> adj[]){
    // Verifica se pode colocar uma aresta de pai a u, e a coloca caso sim.
    // Corrige recursivamente o representante do vértice u, e de seus adjacentes.
    bool deuCerto;
    rep[u] = pai;

    if(u==pai) return false;

    if(adj[u].empty()) return true;

    for(pair<int,int> v : adj[u]){
        deuCerto = corrigeRep(v.first, pai, rep, adj);
        if(!deuCerto) return false;
    }

    return deuCerto;
}


void grafo::montaGrafo(string filename){
    // Para cada aresta na lista (de maior a menor peso), coloca ela no grafo caso
    // não forme circuito, e corrige os representantes dos vértices adjacentes.
    vector<aresta> lista;
    lista = montaListaAdj(filename);
    remove("lista");    //remove o arquivo que não será mais utilizado

    int nArestas = lista.size();
    int repAux[nVertices];    //vetor auxiliar para corrigir rep[], a cada passo
    for(int i=0; i<nVertices; i++) repAux[i] = rep[i];

    for(int i=0; i<nArestas; i++){
        int u = lista[i].second.first;
        int v = lista[i].second.second;

        if(corrigeRep(v, u, repAux, adj)){
            //caso a aresta não forme circuito, coloca ela
            int peso = lista[i].first;
            adj[u].push_back(make_pair(v,peso));
            for(int i=0; i<nVertices; i++) rep[i] = repAux[i];    //atualiza rep[]
        }

        else{
            for(int i=0; i<nVertices; i++) repAux[i] = rep[i];
        }
    }
}


vector<int> encontraRepresentantes(int rep[], int nVertices){
    // Retorna todos os diferentes representantes, que podem ser utilizados
    // como vértice de início na remontagem do maior caminho.
    vector<int> representantes;
    int i;
    
    int aux[nVertices];
    for(i=0; i<nVertices; i++) aux[i] = 0;

    for(i=0; i<nVertices; i++){
        aux[rep[i]] = 1;
    }

    for(i=0; i<nVertices; i++){
        if(aux[i]==1) representantes.push_back(i);
    }

    return representantes;
}


void maiorCamihnoRep(vector<pair<int,int>> adj[], int u, vector<int> aux, int caminho[], int *tamanhoCaminho){
    // Acha o maior caminho no grafo partindo de um representante, recursivamente.
    aux.push_back(u);

    if(adj[u].empty()){
        if(aux.size() > *tamanhoCaminho){
            for(int i=0; i<*tamanhoCaminho; i++) caminho[i] = 0;
            for(int i=0; i<aux.size(); i++) caminho[i] = aux[i];
            *tamanhoCaminho = aux.size();
        }
        return;
    }

    for(pair<int,int> v : adj[u]){
        maiorCamihnoRep(adj, v.first, aux, caminho, tamanhoCaminho);
        // como o vector passado como parâmetro não tem seus valores mudados, como um vetor
        // normal teria, não é preciso remover o caminho feito quando volta na recursão.
    }
}


vector<int> maiorCaminho(int rep[], int nVertices, vector<pair<int,int>> adj[]){
    // Retorna uma lista do maior caminho (em número de vértices) no grafo, onde:
    // O primeiro elemento da lista é o vértice inicial,
    // e cada novo elemento é o próximo vértice
    vector<int> representantes = encontraRepresentantes(rep, nVertices);
    vector<int> aux;
    int caminho[nVertices], maiorCamihno[nVertices], tamanhoCaminho=0, tamanhoMaiorCaminho=0;
    
    // para cada representante onde pode começar, busca o maior caminho.
    for(int v : representantes){
        maiorCamihnoRep(adj, v, aux, caminho, &tamanhoCaminho);
        if(tamanhoCaminho > tamanhoMaiorCaminho){
            tamanhoMaiorCaminho = tamanhoCaminho;
            for(int i=0; i<tamanhoCaminho; i++) maiorCamihno[i] = caminho[i];
        }
        aux.clear();
        for(int i=0; i<tamanhoCaminho; i++) caminho[i] = 0;
    }
    
    aux.clear();
    for(int i=0; i<tamanhoCaminho; i++) aux.push_back(maiorCamihno[i]);
    return aux;
}


string grafo::remonta(){
    string dna, proxFragmento;
    vector<int> caminho;
    caminho = maiorCaminho(rep, nVertices, adj);
    int tamanhoCaminho = caminho.size();
    int peso;

    int vertice = caminho[0];
    dna = fragmentos[vertice];

    for(int i=1; i<tamanhoCaminho; i++){
        
        for(pair<int,int> v : adj[vertice]){
            if(caminho[i] != v.first) continue;
            else peso = v.second;
        }

        proxFragmento = fragmentos[caminho[i]];

        proxFragmento.erase(0, peso);
        dna.append(proxFragmento);

        vertice = caminho[i];
    }

    return dna;
}