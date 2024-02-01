#include <iostream>
#include "grafo.h"
#include <fstream>
#include <stack>
#include <algorithm>

using namespace std;



string corrigeExpreg(string expreg){
    // Corrige uma expressão regular, para os casos particulares
    // Recebe a expreg, e retorna uma expreg corrigida
    string corrigida;
    int i;
    corrigida.append("("); corrigida.append(expreg); corrigida.append(")");    //ajuda em casos de exceção
    expreg.clear();
    expreg.append(corrigida);
    corrigida.clear();

    // corrige [
    for(i=0; i<expreg.length(); i++){
        string aux = " ";
        aux[0] = expreg[i];
        if(expreg[i]=='[' && (i>0 && expreg[i-1]!='\\')){
            corrigida.append("(");
            corrigida.append(aux);
        }
        else if(expreg[i]==']' && (i>0 && expreg[i-1]!='\\')){
            corrigida.append(aux);
            corrigida.append(")");
        }
        else corrigida.append(aux);
    }
    expreg.clear(); expreg.append(corrigida);
    corrigida.clear();

    // corrige * e +
    for(i=0; i<expreg.length()-1; i++){
        string aux = " ";
        aux[0] = expreg[i];
        if((expreg[i+1]=='*' || expreg[i+1]=='+') && (expreg[i]!=')' && expreg[i]!='\\')){
            corrigida.append("(");
            corrigida.append(aux);
            corrigida.append(")");
        }
        else corrigida.append(aux);
    }
    string aux = " ";
    aux[0] = expreg[i];
    corrigida.append(aux);
    expreg.clear();
    expreg.append(corrigida);

    // corrige |
    corrigida.clear();
    stack<int> pilha;
    int ini;
    int tamanho = expreg.length();

    for(i=0; i<tamanho; i++){
        if(expreg[i]=='('){
            if(!(i>0 && expreg[i-1]=='\\')){
                pilha.push(i);
            }
        }

        else if(expreg[i]==')' && (i>0 && expreg[i-1]!='\\')){
            int alternativas=0;
            ini = pilha.top(); pilha.pop();
            for(int j=ini+1; j<i; j++){
                if(expreg[j]=='|' && (j>0 && expreg[j-1]!='\\')){
                    alternativas++;
                }
            }

            if(alternativas>1){
                //copia até os parênteses
                corrigida.append(expreg.substr(0, ini+1));
                //abre todos os parênteses das altarnativas
                for(int j=0; j<alternativas-1; j++){
                    corrigida.append("(");
                }
                //vai copiando as alternativas e fechando os parênteses delas
                bool pula=true;
                for(int j=ini+1; j<i; j++){
                    //pula os parenteses no meio
                    if(expreg[j]=='(' && (j>0 && expreg[j-1]!='\\')){
                        int aFechar=1;
                        corrigida.append("(");
                        j++;
                        while(aFechar>0){
                            if(expreg[j]==')' && (j>0 && expreg[j-1]!='\\')) aFechar--;
                            else if(expreg[j]=='(' && (j>0 && expreg[j-1]!='\\')) aFechar++;
                            string aux = " ";
                            aux[0] = expreg[j];
                            corrigida.append(aux);
                            j++;
                        }
                        j--;
                    }
                    //fecha os parênteses das alternativas
                    else if(expreg[j]=='|' && (j>0 && expreg[j-1]!='\\') && pula){
                        pula = false;    //não fecha o primeiro
                        corrigida.append("|");
                    }
                    else if(expreg[j]=='|' && (j>0 && expreg[j-1]!='\\') && !pula){
                        corrigida.append(")|");
                    }
                    else{
                        string aux = " ";
                        aux[0] = expreg[j];
                        corrigida.append(aux);
                    }
                }
                //copia o que vem depois dos parênteses
                corrigida.append(expreg.substr(i));
                //corrige os índices com a expreg atualizada
                i += (alternativas-1)*2;
                tamanho += (alternativas-1)*2;
            
                expreg.clear();
                expreg.append(corrigida);
                corrigida.clear();
            }
        }
    }
    return expreg;
}


grafo montaNDFA(string expreg){
    // Monta o grafo não determinístico
    // Recebe a expreg e retorna um grafo
    stack<int> pilha;
    grafo G(expreg.length());

    for(int i=0; i<expreg.length(); i++){
        int ant;

        // Caso ( ou |
        if(expreg[i]=='(' || expreg[i]=='|'){
            pilha.push(i);
        }

        // Caso )
        else if(expreg[i]==')'){
            int carTopo=pilha.top(); pilha.pop();
            if(expreg[carTopo]=='|'){
                ant=pilha.top(); pilha.pop();
                G.incluiArco(ant, carTopo+1);   
                G.incluiArco(carTopo, i+1);
            }
            else ant = carTopo;
        }

        // Caso *
        if(expreg[i]=='*'){
            G.incluiArco(ant, i+1);
            G.incluiArco(i, ant);
            G.incluiArco(i, i+1);
        }

        // Caso +
        if(expreg[i]=='+'){
            G.incluiArco(i, ant);
            G.incluiArco(i, i+1);
        }

        // Parenteses
        if(expreg[i]=='(' || expreg[i]==')'){
            G.incluiArco(i, i+1);
        }


        // Caso leitura
        if(expreg[i]!='(' && expreg[i]!=')' && expreg[i]!='|' && expreg[i]!='*' && expreg[i]!='+'){
            // caso []
            if(expreg[i]=='['){
                // complemento
                if(expreg[i+1]=='^'){
                    //intervalo
                    if(expreg[i+3]=='-'){
                        G.nosLeitura[i].tipo = 4;
                        G.nosLeitura[i].ini = expreg[i+2];
                        G.nosLeitura[i].fim = expreg[i+4];
                        G.incluiArco(i+1, i+6);
                        i += 5;
                    }
                    //conjunto
                    else{
                        G.nosLeitura[i].tipo = 2;
                        int aux=i+2;
                        while(expreg[aux]!=']'){
                            G.nosLeitura[i].conjunto.push_back(expreg[aux]);
                            aux++;
                        }
                        G.incluiArco(i+1, aux+1);
                        i = aux;
                    }
                }

                // sem complemento
                else{
                    //intervalo
                    if(expreg[i+2]=='-'){
                        G.nosLeitura[i].tipo = 3;
                        G.nosLeitura[i].ini = expreg[i+1];
                        G.nosLeitura[i].fim = expreg[i+3];
                        G.incluiArco(i+1, i+5);
                        i += 4;
                    }
                    //conjunto
                    else{
                        G.nosLeitura[i].tipo = 1;
                        int aux=i+1;
                        while(expreg[aux]!=']'){
                            G.nosLeitura[i].conjunto.push_back(expreg[aux]);
                            aux++;
                        }
                        G.incluiArco(i+1, aux+1);
                        i = aux;
                    }
                }
            }

            // caso .
            else if(expreg[i]=='.'){
                G.nosLeitura[i].tipo = 5;
            }

            // caso "\"
            else if(expreg[i]=='\\'){
                G.incluiArco(i+1, i+2);
                G.nosLeitura[i].tipo = 0;
                G.nosLeitura[i].letra = expreg[i+1];
                i++;
            }

            // caso letra
            else{
                G.nosLeitura[i].tipo = 0;
                G.nosLeitura[i].letra = expreg[i];
            }
        }
    }
    return G;
}


vector<int> dfs(int v, grafo G){
    // Retorna a lista de nós de leitura onde é possível chegar a partir do vértice v
    // Faz uma dfs iterativa com pilha
    bool vis[G.V];
    for(int i=0; i<G.V; i++){
        vis[i] = false;
    }

    vector<int> lista;
    stack<int> pilha;
    
    pilha.push(v);
    while(!pilha.empty()){

        v=pilha.top(); pilha.pop();
        if(!vis[v]){
            vis[v] = true;
            if(G.nosLeitura[v].tipo!=-1){
                lista.push_back(v);
            }
        }

        for(int s=0; s<G.adj[v].size(); s++){
            if(!vis[G.adj[v][s]]){
                pilha.push(G.adj[v][s]);
            }
        }
    }

    return lista;
}


vector<int> *proximos;
void inicializaProximos(grafo G){
    // inicializa o vetor de próximos, utilizado em reconhece()
    for(int i=0; i<G.V; i++){
        proximos[i] = dfs(i, G);
    }
}

bool reconhece(grafo G, string palavra){
    // Reconhece uma palavra a partir de um NDFA
    // Recebe o NDFA, e uma palavra, e retorna verdadeiro se reconhhece, false caso contrário

    vector<int> atuais, alcancados;
    // alcançados têm os vertices de leitura alcançados,
    // atuais têm os vértices seguintes dos de leitura, em que o caractere foi aceito
    
    alcancados = proximos[0];
    bool jaTaNaLista=false;
    for(int i=0; i<palavra.length(); i++){
        // acha os vértices que podem resultar dos lidos
        for(int j=0; j<alcancados.size(); j++){
            if(aceita(G.nosLeitura[alcancados[j]], palavra[i])){
                //aceita caso consiga ler. Um vértice de fim de palavra nunca é aceito
                atuais.push_back(alcancados[j]+1);
            }
        }
        alcancados.clear();

        // acha os vértces que pode estar em seguida
        for(int j=0; j<atuais.size(); j++){
            int atual = atuais[j];
            for(int k=0; k<proximos[atual].size(); k++){
                for(int l=0; l<alcancados.size(); l++){
                    if(proximos[atual][k]==alcancados[l]){
                        jaTaNaLista=true;
                        break;
                    }
                }
                if(!jaTaNaLista) alcancados.push_back(proximos[atual][k]);
                jaTaNaLista = false;
            }
        }
        atuais.clear();

        // se não chega em nenhum nó, não consegue reconhecer palavra
        if(alcancados.empty()) return false;
    }

    // quando termina a palavra, ve se é aceita
    for(int i=0; i<alcancados.size(); i++){
        if(G.nosLeitura[alcancados[i]].tipo==6) return true;
    }
    return false;
}


int main(){
    // lendo a expreg
    string expreg;
    cin >> expreg;
    expreg = corrigeExpreg(expreg);

    // montando o NDFA
    grafo NDFA(expreg.length());
    NDFA = montaNDFA(expreg);
    proximos = new vector<int>[NDFA.V];
    inicializaProximos(NDFA);

    // lendo as palavras
    int n;
    cin >> n;
    string palavras[n];
    for(int i=0; i<n; i++){
        cin >> palavras[i];
    }
    
    // reconhecendo as palavras
    for(int i=0; i<n; i++){
        if(reconhece(NDFA, palavras[i])) cout << "S\n";
        else cout << "N\n";
    }
}