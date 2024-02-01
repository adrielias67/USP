#include <iostream>
#include "as.h"
#include <algorithm>
#include <cmath>

using namespace std;



int max_pot_2(int x){
    //retorna o expoente da maior potencia de 2 menor ou igual a x
    int p=0;
    while(pow(2,p) < x) p++;
    return p-1;
}


no_as* monta_ate_h(no_as* no, int h_no, int h){
    // monta a árvore nivelada até a altura h (potência de 2)
    no_as* novo = new(no_as);
    novo->h = h_no;
    if(h_no == h) return novo;
    novo->esq = monta_ate_h(no, h_no+1, h);
    novo->dir = monta_ate_h(no, h_no+1, h);
    return novo;
}


int sobra;
void adiciona_sobra(no_as* no){
    // adiciona as folhas que não cabem na potência de 2
    if(sobra == 0) return;
    
    if(no->esq==nullptr && no->dir==nullptr){
        no->esq = new(no_as);
        no->esq->h = no->h+1;
        no->dir = new(no_as);
        no->dir->h = no->h+1;
        sobra --;
        return;
    }

    adiciona_sobra(no->esq);
    if(sobra == 0) return;
    adiciona_sobra(no->dir);
}


vector<int> folhas;
bool intervalo = false;    // itera entre aberto e fechado para preencher os intervalos das folhas

no_as* preenche_intervalos(no_as* no){
    // folha
    if(no->esq==nullptr && no->dir==nullptr){
        if(intervalo){
            no->ini = folhas[0];
            no->fim = folhas[0];
            no->ini_fechado = true;
            no->fim_fechado = true;
        }
        else{
            no->ini = folhas[0];
            no->fim = folhas[1];
            no->ini_fechado = false;
            no->fim_fechado = false;
            folhas.erase(folhas.begin(), folhas.begin()+1);
        }
        intervalo = !intervalo;
        return no;
    }

    // preenche recursivamente e corrige subindo
    no->esq = preenche_intervalos(no->esq);
    no->dir = preenche_intervalos(no->dir);
    no->ini_fechado = no->esq->ini_fechado;
    no->fim_fechado = no->dir->fim_fechado;
    no->ini = no->esq->ini;
    no->fim = no->dir->fim;
    return no;
}


bool contem_intervalo(pair<int,int> A, no_as* B){
    // retorna se o intervalo A contém o intervalo B de um nó
    if(A.first > B->ini) return false;
    if(A.second < B->fim) return false;
    return true;
}


void preenche_segmento(no_as* no, pair<int,int> seg, int seg_num){
    // preenche um segmento na árvore recursivamente
    if(contem_intervalo(seg, no)){
        no->lista.push_back(seg_num);
        return;
    }
    if(no->esq==nullptr && no->dir==nullptr) return;
    preenche_segmento(no->esq, seg, seg_num);
    preenche_segmento(no->dir, seg, seg_num);
}


as::as(lista_seg S){
    for(int i=0; i<S.size(); i++){    // utilizado na ASD
        segmentos.push_back(S[i]);
    }
    reverse(segmentos.begin(), segmentos.end());    // precisa estar na ordem

    // elimina as repeticões
    for(int i=0; i<S.size(); i++){
        folhas.push_back(S[i].first);
        folhas.push_back(S[i].second);
    }
    sort(folhas.begin(), folhas.end());
    folhas.erase(unique(folhas.begin(), folhas.end()), folhas.end());

    // calcula a altura da árvore em potência de 2 e a sobra
    int n_folhas = folhas.size() * 2 + 1;
    int h = max_pot_2(n_folhas);
    sobra = n_folhas - pow(2,h);

    // monta a árvore vazia
    raiz = monta_ate_h(raiz, 0, h);
    adiciona_sobra(raiz);

    // adiciona os intervalos
    folhas.push_back(INT32_MAX);
    folhas.push_back(INT32_MIN);
    sort(folhas.begin(), folhas.end());
    preenche_intervalos(raiz);

    // adiciona os segmentos
    for(int i=0; i<S.size(); i++){
        preenche_segmento(raiz, S[i], i+1);
    }
}


as::~as(){
}


bool contem_x(no_as* no, int x){
    // retorna se o nó contém o ponto x
    if(no->ini_fechado && no->ini == x) return true;
    if(no->fim_fechado && no->fim == x) return true;
    if(no->ini < x && no->fim > x) return true;
    return false;
}


vector<int> as::Segments(no_as* no, int x){
    vector<int> segs;
    // desce até o x, adicionando os segmentos no caminho
    while(no->esq != nullptr && no->dir != nullptr){
        if(contem_x(no->esq, x)){
            for(int i=0; i<no->esq->lista.size(); i++){
                segs.push_back(no->esq->lista[i]);
            }
            no = no->esq;
        }
        else{
            for(int i=0; i<no->dir->lista.size(); i++){
                segs.push_back(no->dir->lista[i]);
            }
            no = no->dir;
        }
    }
    return segs;
}




void printR(no_as* no){
    if(no==nullptr) return;

    printR(no->esq);

    for(int i=0; i<no->h; i++) cout << "   ";
    
    if(no->ini_fechado) cout << "[";
    else cout << "(";
        
    if(no->ini==INT32_MIN) cout << "-inf";
    else cout << no->ini;
    cout << ",";
    if(no->fim==INT32_MAX) cout << "+inf";
    else cout << no->fim;

    if(no->fim_fechado) cout << "]";
    else cout << ")";

    for(int i=0; i<no->lista.size(); i++){
        cout << " " << no->lista[i];
    }
        
    cout << endl;

    printR(no->dir);
}


void as::Print(no_as* r){
    printR(r);
    cout << endl;
}