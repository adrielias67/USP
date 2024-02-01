#include <iostream>
#include <algorithm>
#include "deque.h"
using namespace std;

int ID=0;



no::no(item val, int height, no* Parent, no* Jump){
    value = val;
    depth = height;
    parent = Parent;
    jump = Jump;
}


no *level_ancestor(int k, no u){
    // retorna um ponteiro para o level ancestor k de um nó
    // não é possível retornar quando k=0, portanto são feitas verificações no código antes de level_ancestor() ser usado
    int y = u.depth-k+1;
    while(u.depth!=y){
        if(u.jump->depth >= y){
            u = *u.jump;
        }
        else{
            u = *u.parent;
        }
    }
    return u.parent;
}


no lowest_common_ancestor(no u, no v){
    // retorna o lca de 2 nós
    if(u.depth > v.depth){
        u = *level_ancestor(u.depth-v.depth, u);
    }
    if(u.depth < v.depth){
        v = *level_ancestor(v.depth-u.depth, v);
    }
    if(u.id==v.id) return u;

    while(u.parent!=v.parent){
        if(u.jump != v.jump){
            u = *u.jump;
            v = *v.jump;
        }
        else{
            u = *u.parent;
            v = *v.parent;
        }
    }

    return *u.parent;
}



deque::deque(){
    no* novo = new no(0, 0, nullptr, nullptr);
    novo->id = ID++;
    inis.push_back(novo);
    fins.push_back(novo);
}


deque::~deque(){
    inis.clear();
    fins.clear();
}


item deque::front(int d){
    return inis[d]->value;
}


item deque::back(int d){
    return fins[d]->value;
}


void deque::push_front(int d, item x){
    no* ini = inis[d];
    no* fim = fins[d];

    // Caso da raíz
    if(ini->id == 0){
        no* novo = new no(x, 1, ini, fim);
        novo->id = ID++;
        inis.push_back(novo);
        fins.push_back(novo);
        return;
    }

    // Calcula o jump
    no* j;
    if(ini->jump->id!=0 && (ini->depth - ini->jump->depth == ini->jump->depth - ini->jump->jump->depth)){
        j = ini->jump->jump;
    }
    else j = ini;

    // Cria  o nó
    no* novo = new no(x, ini->depth+1, ini, j);
    novo->id = ID++;
    inis.push_back(novo);
    fins.push_back(fim);
}


void deque::push_back(int d, item x){
    no* ini = inis[d];
    no* fim = fins[d];

    // Caso da raíz
    if(fim->id == 0){
        no* novo = new no(x, 1, ini, fim);
        novo->id = ID++;
        inis.push_back(novo);
        fins.push_back(novo);
        return;
    }

    // Calcula o jump
    no* j;
    if(fim->jump->id!=0 && (fim->depth - fim->jump->depth == fim->jump->depth - fim->jump->jump->depth)){
        j = fim->jump->jump;
    }
    else j = fim;

    // Cria  o nó
    no* novo = new no(x, fim->depth+1, fim, j);
    novo->id = ID++;
    inis.push_back(ini);
    fins.push_back(novo);
}


void deque::pop_front(int d){
    no* ini = inis[d];
    no* fim = fins[d];

    // Caso da deque com 1 elemento só
    if(ini->id == fim->id){
        inis.push_back(inis[0]);
        fins.push_back(inis[0]);
        return;
    }

    no lca = lowest_common_ancestor(*ini, *fim);

    // Caso da deque onde o lca é o início
    if(lca.id == ini->id){
        // caso de exceção do level_ancestor() para deque com 2 elementos
        if(fim->depth-ini->depth-1 == 0){
            inis.push_back(fim);
            fins.push_back(fim);
        }
        // caso normal
        else{
            no* ini_new = level_ancestor(fim->depth - ini->depth -1 ,*fim);
            inis.push_back(ini_new);
            fins.push_back(fim);
        }
    }

    //Caso da deque onde o lca não é o início
    else{
        inis.push_back(ini->parent);
        fins.push_back(fim);
    }
}


void deque::pop_back(int d){
    no* ini = inis[d];
    no* fim = fins[d];

    // Caso da deque com 1 elemento só
    if(ini->id == fim->id){
        inis.push_back(inis[0]);
        fins.push_back(inis[0]);
        return;
    }

    no lca = lowest_common_ancestor(*ini, *fim);

    // Caso da deque onde o lca é o início
    if(lca.id == fim->id){
        // caso de exceção do level_ancestor() para deque com 2 elementos
        if(fim->depth-ini->depth-1 == 0){
            inis.push_back(ini);
            fins.push_back(ini);
        }
        // caso normal
        else{
            no* fim_new = level_ancestor(ini->depth - fim->depth -1 ,*ini);
            inis.push_back(ini);
            fins.push_back(fim_new);
        }
    }

    //Caso da deque onde o lca não é o início
    else{
        inis.push_back(ini);
        fins.push_back(fim->parent);
    }
}


item deque::k_th(int d, int k){
    k--;    // do jeito que o código foi feito é mais fácil fazer o k-th de uma deque começando com índice 0
    no* ini = inis[d];
    no* fim = fins[d];

    if(k==0) return ini->value;    // caso de exceção
    no lca = lowest_common_ancestor(*ini, *fim);

    // Caso em que o k-ésimo elemento está antes do lca (ou é o próprio)
    if(k <= ini->depth - lca.depth)
        return level_ancestor(k, *ini)->value;
    
    // Caso em que o k-ésimo elemento está depois do lca
    if(fim->depth-2*lca.depth-k+ini->depth == 0) return fim->value;    // caso de exceção do level_ancestor()
    return level_ancestor(fim->depth - 2*lca.depth - k + ini->depth, *fim)->value;    // caso normal
}


void deque::print(int d){
    no* ini = inis[d];
    no* fim = fins[d];

    int lca_depth = lowest_common_ancestor(*ini, *fim).depth;
    no atual = *ini;

    // imprime até o lca
    for(int i=ini->depth; i>=lca_depth; i--){
        cout << atual.value << " ";
        atual = *atual.parent;
    }

    // para caso o lca já seja o fim
    if(atual.id == fim->id){
        cout << endl;
        return;
    }

    // imprime inverso depois do lca
    vector <int> aux;
    atual = *fim;
    for(int i=fim->depth; i>lca_depth; i--){
        aux.push_back(atual.value);
        atual = *atual.parent;
    }
    for(int i=fim->depth; i>lca_depth; i--){
        cout << aux.back() << " ";
        aux.pop_back();
    }
    cout << endl;
}