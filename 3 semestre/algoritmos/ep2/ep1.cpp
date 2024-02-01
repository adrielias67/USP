#include<iostream>
#include<vector>
#include<stdlib.h>
#include"palavra.h"
#include"vetorOrdenado.h"
#include"arvoreBB.h"
#include"treap.h"
#include"arvore23.h"
#include"arvoreRN.h"
#include"string.h"

using namespace std;

#define PALAVRA_MAX 100



//Key corrigePalavra(Key palavra);
void VO();
void ABB();
void TR();
void A23();
void ARN();


int tamanhoTexto;

int main(){
    char * opcao = new char[4];
    bool opcaoInvalida=true;

    while(opcaoInvalida){
        cin >> opcao;
        if(strcmp(opcao, "VO")==0){
            VO();
            opcaoInvalida = false;
        }
        else if(strcmp(opcao, "ABB")==0){
            ABB();
            opcaoInvalida = false;
        }
        else if(strcmp(opcao, "TR")==0){
            TR();
            opcaoInvalida = false;
        }
        else if(strcmp(opcao, "A23")==0){
            A23();
            opcaoInvalida = false;
        }
        else if(strcmp(opcao, "ARN")==0){
            ARN();
            opcaoInvalida = false;
        }
        else cout << "Opcao invalida!\n";
    }

    return 0;
}





Key corrigePalavra(Key palavra){
    // dada uma palavra, retira caracteres estranhos dela
    int i=0, j=0;

    /*acha o começo da palavra*/
    while(palavra[i]!='\0' && (palavra[i]>'z' || (palavra[i]>'Z' && palavra[i]<'a') || (palavra[i]<'A' && palavra[i]>'9')  || palavra[i]<'0' || palavra[i]=='-')) i++;

    for(j=0; j<palavra.length()-i; j++){
        palavra[j] = palavra[j+i];
    }
    palavra[j] = '\0';

    /*copia a palavra*/
    i = j-1;
    while(i>0 && (palavra[i]>'z' || (palavra[i]>'Z' && palavra[i]<'a') || (palavra[i]<'A' && palavra[i]>'9')  || palavra[i]<'0' || palavra[i]=='-')){    
        i--;
    }
    palavra.erase(i+1, palavra.length()-i);

    return palavra;
}





void VO(){
    /* input do texto */
    cin >> tamanhoTexto;
    vetorOrdenado VetorOrdenado;
    Key palavra;
    item valor;
    vector<Key> maisFrequentes, maisLongas, SR, VD;
    int nOcorrenciasMaisFreq=0, tamanhoMaisLonga=0, tamanhoSR=0, tamanhoVD=PALAVRA_MAX, nVogaisVD=-1;

    for(int i=0; i<tamanhoTexto; i++){
        cin >> palavra;
        palavra = corrigePalavra(palavra);
        valor = valor.inicializa(palavra);
        VetorOrdenado.add(palavra, valor);


        /* atualiza os vetores de consultas */
        /*atualiza mais frequentes*/
        if(VetorOrdenado.value(palavra).nOcorrencias > nOcorrenciasMaisFreq){
            nOcorrenciasMaisFreq = VetorOrdenado.value(palavra).nOcorrencias; 
            maisFrequentes.clear();
            maisFrequentes.push_back(palavra);
        }
        else if(VetorOrdenado.value(palavra).nOcorrencias == nOcorrenciasMaisFreq){
            bool nova = true;
            for(int i=0; i<maisFrequentes.size(); i++){
                if(maisFrequentes[i] == palavra) nova = false;
            }
            if(nova) maisFrequentes.push_back(palavra);
        }

        /*atualiza mais longas*/
        if(valor.nLetras > tamanhoMaisLonga){
            int j=0;
            tamanhoMaisLonga = valor.nLetras;
            maisLongas.clear();
            maisLongas.push_back(palavra);
        }
        else if(valor.nLetras == tamanhoMaisLonga){
            bool nova = true;
            for(int i=0; i<maisLongas.size(); i++){
                if(maisLongas[i] == palavra) nova = false;
            }
            if(nova) maisLongas.push_back(palavra);
        }

        /*atualiza maiores palavras que nao repetem letras*/
        if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras>tamanhoSR){
            tamanhoSR = valor.nLetras;
            SR.clear();
            SR.push_back(palavra);
        }
        else if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras==tamanhoSR){
            bool nova = true;
            for(int i=0; i<SR.size(); i++){
                if(SR[i] == palavra) nova = false;
            }
            if(nova) SR.push_back(palavra);
        }

        /*atualiza menores palavras com mais vogais sem repetição*/
        if((valor.nVD(palavra, valor.nLetras)>nVogaisVD) || (valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras<tamanhoVD)){
            nVogaisVD = valor.nVD(palavra, valor.nLetras);
            tamanhoVD = valor.nLetras;
            VD.clear();
            VD.push_back(palavra);
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras==tamanhoVD){
            bool nova = true;
            for(int i=0; i<VD.size(); i++){
                if(VD[i] == palavra) nova = false;
            }
            if(nova) VD.push_back(palavra);
        }
    }
    

    /* consultas / queries */
    int Q;
    char * query = new char[3];
    cin >> Q;
    while(Q>0){
        cin >> query;
        int i;

        if(strcmp(query, "F")==0){
            for(i=0; i<maisFrequentes.size(); i++){
                cout << maisFrequentes[i] << " ";
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "O")==0){
            Key Opalavra;
            cin >> Opalavra;
            cout << VetorOrdenado.value(Opalavra).nOcorrencias << endl;
            Q--;
        }

        else if(strcmp(query, "L")==0){
            for(i=0; i<maisLongas.size(); i++){
                cout << maisLongas[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "SR")==0){
            for(i=0; i<SR.size(); i++){
                cout << SR[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "VD")==0){
            for(i=0; i<VD.size(); i++){
                cout << VD[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else cout << "Consulta invalida!\n";
    }
}



void ABB(){
    /* input do texto */
    cin >> tamanhoTexto;
    arvoreBB ArvoreBB;
    Key palavra;
    item valor;
    vector<Key> maisFrequentes, maisLongas, SR, VD;
    int nOcorrenciasMaisFreq=0, tamanhoMaisLonga=0, tamanhoSR=0, tamanhoVD=PALAVRA_MAX, nVogaisVD=-1;

    for(int i=0; i<tamanhoTexto; i++){
        cin >> palavra;
        palavra = corrigePalavra(palavra);
        valor = valor.inicializa(palavra);
        ArvoreBB.add(palavra, valor);


        /* atualiza os vetores de consultas */
        /*atualiza mais frequentes*/
        if(ArvoreBB.value(palavra).nOcorrencias > nOcorrenciasMaisFreq){
            nOcorrenciasMaisFreq = ArvoreBB.value(palavra).nOcorrencias; 
            maisFrequentes.clear();
            maisFrequentes.push_back(palavra);
        }
        else if(ArvoreBB.value(palavra).nOcorrencias == nOcorrenciasMaisFreq){
            bool nova = true;
            for(int i=0; i<maisFrequentes.size(); i++){
                if(maisFrequentes[i] == palavra) nova = false;
            }
            if(nova) maisFrequentes.push_back(palavra);
        }

        /*atualiza mais longas*/
        if(valor.nLetras > tamanhoMaisLonga){
            int j=0;
            tamanhoMaisLonga = valor.nLetras;
            maisLongas.clear();
            maisLongas.push_back(palavra);
        }
        else if(valor.nLetras == tamanhoMaisLonga){
            bool nova = true;
            for(int i=0; i<maisLongas.size(); i++){
                if(maisLongas[i] == palavra) nova = false;
            }
            if(nova) maisLongas.push_back(palavra);
        }

        /*atualiza maiores palavras que nao repetem letras*/
        if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras>tamanhoSR){
            tamanhoSR = valor.nLetras;
            SR.clear();
            SR.push_back(palavra);
        }
        else if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras==tamanhoSR){
            bool nova = true;
            for(int i=0; i<SR.size(); i++){
                if(SR[i] == palavra) nova = false;
            }
            if(nova) SR.push_back(palavra);
        }

        /*atualiza menores palavras com mais vogais sem repetição*/
        if((valor.nVD(palavra, valor.nLetras)>nVogaisVD) || (valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras<tamanhoVD)){
            nVogaisVD = valor.nVD(palavra, valor.nLetras);
            tamanhoVD = valor.nLetras;
            VD.clear();
            VD.push_back(palavra);
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras==tamanhoVD){
            bool nova = true;
            for(int i=0; i<VD.size(); i++){
                if(VD[i] == palavra) nova = false;
            }
            if(nova) VD.push_back(palavra);
        }
    }
    

    /* consultas / queries */
    int Q;
    char * query = new char[3];
    cin >> Q;
    while(Q>0){
        cin >> query;
        int i;

        if(strcmp(query, "F")==0){
            for(i=0; i<maisFrequentes.size(); i++){
                cout << maisFrequentes[i] << " ";
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "O")==0){
            Key Opalavra;
            cin >> Opalavra;
            cout << ArvoreBB.value(Opalavra).nOcorrencias << endl;
            Q--;
        }

        else if(strcmp(query, "L")==0){
            for(i=0; i<maisLongas.size(); i++){
                cout << maisLongas[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "SR")==0){
            for(i=0; i<SR.size(); i++){
                cout << SR[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "VD")==0){
            for(i=0; i<VD.size(); i++){
                cout << VD[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else cout << "Consulta invalida!\n";
    }
}



void TR(){
    /* input do texto */
    cin >> tamanhoTexto;
    treap Treap;
    Key palavra;
    item valor;
    vector<Key> maisFrequentes, maisLongas, SR, VD;
    int nOcorrenciasMaisFreq=0, tamanhoMaisLonga=0, tamanhoSR=0, tamanhoVD=PALAVRA_MAX, nVogaisVD=-1;

    for(int i=0; i<tamanhoTexto; i++){
        cin >> palavra;
        palavra = corrigePalavra(palavra);
        valor = valor.inicializa(palavra);
        Treap.add(palavra, valor);


        /* atualiza os vetores de consultas */
        /*atualiza mais frequentes*/
        if(Treap.value(palavra).nOcorrencias > nOcorrenciasMaisFreq){
            nOcorrenciasMaisFreq = Treap.value(palavra).nOcorrencias; 
            maisFrequentes.clear();
            maisFrequentes.push_back(palavra);
        }
        else if(Treap.value(palavra).nOcorrencias == nOcorrenciasMaisFreq){
            bool nova = true;
            for(int i=0; i<maisFrequentes.size(); i++){
                if(maisFrequentes[i] == palavra) nova = false;
            }
            if(nova) maisFrequentes.push_back(palavra);
        }

        /*atualiza mais longas*/
        if(valor.nLetras > tamanhoMaisLonga){
            int j=0;
            tamanhoMaisLonga = valor.nLetras;
            maisLongas.clear();
            maisLongas.push_back(palavra);
        }
        else if(valor.nLetras == tamanhoMaisLonga){
            bool nova = true;
            for(int i=0; i<maisLongas.size(); i++){
                if(maisLongas[i] == palavra) nova = false;
            }
            if(nova) maisLongas.push_back(palavra);
        }

        /*atualiza maiores palavras que nao repetem letras*/
        if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras>tamanhoSR){
            tamanhoSR = valor.nLetras;
            SR.clear();
            SR.push_back(palavra);
        }
        else if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras==tamanhoSR){
            bool nova = true;
            for(int i=0; i<SR.size(); i++){
                if(SR[i] == palavra) nova = false;
            }
            if(nova) SR.push_back(palavra);
        }

        /*atualiza menores palavras com mais vogais sem repetição*/
        if((valor.nVD(palavra, valor.nLetras)>nVogaisVD) || (valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras<tamanhoVD)){
            nVogaisVD = valor.nVD(palavra, valor.nLetras);
            tamanhoVD = valor.nLetras;
            VD.clear();
            VD.push_back(palavra);
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras==tamanhoVD){
            bool nova = true;
            for(int i=0; i<VD.size(); i++){
                if(VD[i] == palavra) nova = false;
            }
            if(nova) VD.push_back(palavra);
        }
    }
    

    /* consultas / queries */
    int Q;
    char * query = new char[3];
    cin >> Q;
    while(Q>0){
        cin >> query;
        int i;

        if(strcmp(query, "F")==0){
            for(i=0; i<maisFrequentes.size(); i++){
                cout << maisFrequentes[i] << " ";
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "O")==0){
            Key Opalavra;
            cin >> Opalavra;
            cout << Treap.value(Opalavra).nOcorrencias << endl;
            Q--;
        }

        else if(strcmp(query, "L")==0){
            for(i=0; i<maisLongas.size(); i++){
                cout << maisLongas[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "SR")==0){
            for(i=0; i<SR.size(); i++){
                cout << SR[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "VD")==0){
            for(i=0; i<VD.size(); i++){
                cout << VD[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else cout << "Consulta invalida!\n";
    }
}



void A23(){
    /* input do texto */
    cin >> tamanhoTexto;
    arvore23 Arvore23;
    Key palavra;
    item valor;
    vector<Key> maisFrequentes, maisLongas, SR, VD;
    int nOcorrenciasMaisFreq=0, tamanhoMaisLonga=0, tamanhoSR=0, tamanhoVD=PALAVRA_MAX, nVogaisVD=-1;

    for(int i=0; i<tamanhoTexto; i++){
        cin >> palavra;
        palavra = corrigePalavra(palavra);
        valor = valor.inicializa(palavra);
        Arvore23.add(palavra, valor);


        /* atualiza os vetores de consultas */
        /*atualiza mais frequentes*/
        if(Arvore23.value(palavra).nOcorrencias > nOcorrenciasMaisFreq){
            nOcorrenciasMaisFreq = Arvore23.value(palavra).nOcorrencias; 
            maisFrequentes.clear();
            maisFrequentes.push_back(palavra);
        }
        else if(Arvore23.value(palavra).nOcorrencias == nOcorrenciasMaisFreq){
            bool nova = true;
            for(int i=0; i<maisFrequentes.size(); i++){
                if(maisFrequentes[i] == palavra) nova = false;
            }
            if(nova) maisFrequentes.push_back(palavra);
        }

        /*atualiza mais longas*/
        if(valor.nLetras > tamanhoMaisLonga){
            int j=0;
            tamanhoMaisLonga = valor.nLetras;
            maisLongas.clear();
            maisLongas.push_back(palavra);
        }
        else if(valor.nLetras == tamanhoMaisLonga){
            bool nova = true;
            for(int i=0; i<maisLongas.size(); i++){
                if(maisLongas[i] == palavra) nova = false;
            }
            if(nova) maisLongas.push_back(palavra);
        }

        /*atualiza maiores palavras que nao repetem letras*/
        if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras>tamanhoSR){
            tamanhoSR = valor.nLetras;
            SR.clear();
            SR.push_back(palavra);
        }
        else if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras==tamanhoSR){
            bool nova = true;
            for(int i=0; i<SR.size(); i++){
                if(SR[i] == palavra) nova = false;
            }
            if(nova) SR.push_back(palavra);
        }

        /*atualiza menores palavras com mais vogais sem repetição*/
        if((valor.nVD(palavra, valor.nLetras)>nVogaisVD) || (valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras<tamanhoVD)){
            nVogaisVD = valor.nVD(palavra, valor.nLetras);
            tamanhoVD = valor.nLetras;
            VD.clear();
            VD.push_back(palavra);
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras==tamanhoVD){
            bool nova = true;
            for(int i=0; i<VD.size(); i++){
                if(VD[i] == palavra) nova = false;
            }
            if(nova) VD.push_back(palavra);
        }
    }
    

    /* consultas / queries */
    int Q;
    char * query = new char[3];
    cin >> Q;
    while(Q>0){
        cin >> query;
        int i;

        if(strcmp(query, "F")==0){
            for(i=0; i<maisFrequentes.size(); i++){
                cout << maisFrequentes[i] << " ";
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "O")==0){
            Key Opalavra;
            cin >> Opalavra;
            cout << Arvore23.value(Opalavra).nOcorrencias << endl;
            Q--;
        }

        else if(strcmp(query, "L")==0){
            for(i=0; i<maisLongas.size(); i++){
                cout << maisLongas[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "SR")==0){
            for(i=0; i<SR.size(); i++){
                cout << SR[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "VD")==0){
            for(i=0; i<VD.size(); i++){
                cout << VD[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else cout << "Consulta invalida!\n";
    }
}



void ARN(){
    /* input do texto */
    cin >> tamanhoTexto;
    arvoreRN ArvoreRN;
    Key palavra;
    item valor;
    vector<Key> maisFrequentes, maisLongas, SR, VD;
    int nOcorrenciasMaisFreq=0, tamanhoMaisLonga=0, tamanhoSR=0, tamanhoVD=PALAVRA_MAX, nVogaisVD=-1;

    for(int i=0; i<tamanhoTexto; i++){
        cin >> palavra;
        palavra = corrigePalavra(palavra);
        valor = valor.inicializa(palavra);
        ArvoreRN.add(palavra, valor);


        /* atualiza os vetores de consultas */
        /*atualiza mais frequentes*/
        if(ArvoreRN.value(palavra).nOcorrencias > nOcorrenciasMaisFreq){
            nOcorrenciasMaisFreq = ArvoreRN.value(palavra).nOcorrencias; 
            maisFrequentes.clear();
            maisFrequentes.push_back(palavra);
        }
        else if(ArvoreRN.value(palavra).nOcorrencias == nOcorrenciasMaisFreq){
            bool nova = true;
            for(int i=0; i<maisFrequentes.size(); i++){
                if(maisFrequentes[i] == palavra) nova = false;
            }
            if(nova) maisFrequentes.push_back(palavra);
        }

        /*atualiza mais longas*/
        if(valor.nLetras > tamanhoMaisLonga){
            int j=0;
            tamanhoMaisLonga = valor.nLetras;
            maisLongas.clear();
            maisLongas.push_back(palavra);
        }
        else if(valor.nLetras == tamanhoMaisLonga){
            bool nova = true;
            for(int i=0; i<maisLongas.size(); i++){
                if(maisLongas[i] == palavra) nova = false;
            }
            if(nova) maisLongas.push_back(palavra);
        }

        /*atualiza maiores palavras que nao repetem letras*/
        if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras>tamanhoSR){
            tamanhoSR = valor.nLetras;
            SR.clear();
            SR.push_back(palavra);
        }
        else if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras==tamanhoSR){
            bool nova = true;
            for(int i=0; i<SR.size(); i++){
                if(SR[i] == palavra) nova = false;
            }
            if(nova) SR.push_back(palavra);
        }

        /*atualiza menores palavras com mais vogais sem repetição*/
        if((valor.nVD(palavra, valor.nLetras)>nVogaisVD) || (valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras<tamanhoVD)){
            nVogaisVD = valor.nVD(palavra, valor.nLetras);
            tamanhoVD = valor.nLetras;
            VD.clear();
            VD.push_back(palavra);
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras==tamanhoVD){
            bool nova = true;
            for(int i=0; i<VD.size(); i++){
                if(VD[i] == palavra) nova = false;
            }
            if(nova) VD.push_back(palavra);
        }
    }
    

    /* consultas / queries */
    int Q;
    char * query = new char[3];
    cin >> Q;
    while(Q>0){
        cin >> query;
        int i;

        if(strcmp(query, "F")==0){
            for(i=0; i<maisFrequentes.size(); i++){
                cout << maisFrequentes[i] << " ";
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "O")==0){
            Key Opalavra;
            cin >> Opalavra;
            cout << ArvoreRN.value(Opalavra).nOcorrencias << endl;
            Q--;
        }

        else if(strcmp(query, "L")==0){
            for(i=0; i<maisLongas.size(); i++){
                cout << maisLongas[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "SR")==0){
            for(i=0; i<SR.size(); i++){
                cout << SR[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "VD")==0){
            for(i=0; i<VD.size(); i++){
                cout << VD[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else cout << "Consulta invalida!\n";
    }
}