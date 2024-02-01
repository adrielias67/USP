#include<iostream>
#include<stdlib.h>
#include"palavra.h"
#include"vetorOrdenado.h"
#include"arvoreBB.h"
#include"treap.h"
#include"arvore23.h"
#include"arvoreRN.h"
#include"string.h"

using namespace std;

#define INT_MAX 100



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





// Key corrigePalavra(Key palavra){
//     // dada uma palavra, retira caracteres estranhos dela
//     int i=0, j=0;
//     Key aux;
//     aux[0] = '\0';

//     /*acha o começo da palavra*/
//     while(palavra[i]!='\0' && (palavra[i]>'z' || (palavra[i]>'Z' && palavra[i]<'a') || palavra[i]<'A' || palavra[i]=='-')) i++;

//     /*copia a palavra*/
//     while(palavra[i]!='\0' && ((palavra[i]>='a' && palavra[i]<='z') || (palavra[i]>='A' && palavra[i]<='Z') || palavra[i]=='-')){
//         aux[j] = palavra[i];
//         j++;
//         i++;
//     }

//     aux[j] = '\0';

//     return aux;
// }





void VO(){
    /* input do texto */
    cin >> tamanhoTexto;
    vetorOrdenado VetorOrdenado;
    Key palavra;
    item valor;
    Key maisFrequentes[tamanhoTexto], maisLongas[tamanhoTexto], SR[tamanhoTexto], VD[tamanhoTexto];
    int nOcorrenciasMaisFreq=0, tamanhoMaisLonga=0, tamanhoSR=0, tamanhoVD=INT_MAX, nVogaisVD=-1;

    /*inicializa os vetores de consultas*/
    for(int i=0; i<tamanhoTexto; i++){
        Key nula;
        nula = "\0";
        maisFrequentes[i] = nula;
        maisLongas[i] = nula;
        SR[i] = nula;
        VD[i] = nula;
    }

    for(int i=0; i<tamanhoTexto; i++){
        cin >> palavra;
        //palavra = corrigePalavra(palavra);
        valor = valor.inicializa(palavra);
        VetorOrdenado.add(palavra, valor);


        /* atualiza os vetores de consultas */
        /*atualiza mais frequentes*/
        if(VetorOrdenado.value(palavra).nOcorrencias > nOcorrenciasMaisFreq){
            int j=0;
            nOcorrenciasMaisFreq = VetorOrdenado.value(palavra).nOcorrencias; 
            while(j<tamanhoTexto && maisFrequentes[j]!="\0"){
                maisFrequentes[j] = "\0";
                j++;
            }
            maisFrequentes[0] = palavra;
        }
        else if(VetorOrdenado.value(palavra).nOcorrencias == nOcorrenciasMaisFreq){
            int j=0;
            while(j<tamanhoTexto && maisFrequentes[j]!="\0" && maisFrequentes[j]!=palavra) j++;
            maisFrequentes[j] = palavra;
        }

        /*atualiza mais longas*/
        if(valor.nLetras > tamanhoMaisLonga){
            int j=0;
            tamanhoMaisLonga = valor.nLetras;
            while(j<tamanhoTexto && maisLongas[j]!="\0"){
                maisLongas[j] = "\0";
                j++;
            }
            maisLongas[0] = palavra;
        }
        else if(valor.nLetras == tamanhoMaisLonga){
            int j=0;
            while(j<tamanhoTexto && maisLongas[j]!="\0" && maisLongas[j]!=palavra) j++;
            maisLongas[j] = palavra;
        }

        /*atualiza maiores palavras que nao repetem letras*/
        if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras>tamanhoSR){
            int j=0;
            tamanhoSR = valor.nLetras;
            while(j<tamanhoTexto && SR[j]!="\0"){
                SR[j] = "\0";
                j++;
            }
            SR[0] = palavra;
        }
        else if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras==tamanhoSR){
            int j=0;
            while(j<tamanhoTexto && SR[j]!="\0" && SR[j]!=palavra) j++;
            SR[j] = palavra;
        }

        /*atualiza menores palavras com mais vogais sem repetição*/
        if(valor.nVD(palavra, valor.nLetras)>nVogaisVD){
            int j=0;
            nVogaisVD = valor.nVD(palavra, valor.nLetras);
            tamanhoVD = valor.nLetras;
            while(j<tamanhoTexto && VD[j]!="\0"){
                VD[j] = "\0";
                j++;
            }
            VD[0] = palavra;
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras<tamanhoVD){
            int j=0;
            tamanhoVD = valor.nLetras;
            while(j<tamanhoTexto && VD[j]!="\0"){
                VD[j] = "\0";
                j++;
            }
            VD[0] = palavra;
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras==tamanhoVD){
            int j=0;
            while(j<tamanhoTexto && VD[j]!="\0" && VD[j]!=palavra) j++;
            VD[j] = palavra;
        }
    }
    

    /* consultas / queries */
    int Q;
    char * query = new char[3];
    cin >> Q;
    while(Q>0){
        cin >> query;
        int i=0;

        if(strcmp(query, "F")==0){
            while(i<tamanhoTexto && maisFrequentes[i]!="\0"){
                cout << maisFrequentes[i] << " ";
                i++;
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
            while(i<tamanhoTexto && maisLongas[i]!="\0"){
                cout << maisLongas[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "SR")==0){
            while(i<tamanhoTexto && SR[i]!="\0"){
                cout << SR[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "VD")==0){
            while(i<tamanhoTexto && VD[i]!="\0"){
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
    Key maisFrequentes[tamanhoTexto], maisLongas[tamanhoTexto], SR[tamanhoTexto], VD[tamanhoTexto];
    int nOcorrenciasMaisFreq=0, tamanhoMaisLonga=0, tamanhoSR=0, tamanhoVD=INT_MAX, nVogaisVD=-1;

    /*inicializa os vetores de consultas*/
    for(int i=0; i<tamanhoTexto; i++){
        Key nula;
        nula = "\0";
        maisFrequentes[i] = nula;
        maisLongas[i] = nula;
        SR[i] = nula;
        VD[i] = nula;
    }

    for(int i=0; i<tamanhoTexto; i++){
        cin >> palavra;
        //palavra = corrigePalavra(palavra);
        valor = valor.inicializa(palavra);
        ArvoreBB.add(palavra, valor);


        /* atualiza os vetores de consultas */
        /*atualiza mais frequentes*/
        if(ArvoreBB.value(palavra).nOcorrencias > nOcorrenciasMaisFreq){
            int j=0;
            nOcorrenciasMaisFreq = ArvoreBB.value(palavra).nOcorrencias; 
            while(j<tamanhoTexto && maisFrequentes[j]!="\0"){
                maisFrequentes[j] = "\0";
                j++;
            }
            maisFrequentes[0] = palavra;
        }
        else if(ArvoreBB.value(palavra).nOcorrencias == nOcorrenciasMaisFreq){
            int j=0;
            while(j<tamanhoTexto && maisFrequentes[j]!="\0" && maisFrequentes[j]!=palavra) j++;
            maisFrequentes[j] = palavra;
        }

        /*atualiza mais longas*/
        if(valor.nLetras > tamanhoMaisLonga){
            int j=0;
            tamanhoMaisLonga = valor.nLetras;
            while(j<tamanhoTexto && maisLongas[j]!="\0"){
                maisLongas[j] = "\0";
                j++;
            }
            maisLongas[0] = palavra;
        }
        else if(valor.nLetras == tamanhoMaisLonga){
            int j=0;
            while(j<tamanhoTexto && maisLongas[j]!="\0" && maisLongas[j]!=palavra) j++;
            maisLongas[j] = palavra;
        }

        /*atualiza maiores palavras que nao repetem letras*/
        if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras>tamanhoSR){
            int j=0;
            tamanhoSR = valor.nLetras;
            while(j<tamanhoTexto && SR[j]!="\0"){
                SR[j] = "\0";
                j++;
            }
            SR[0] = palavra;
        }
        else if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras==tamanhoSR){
            int j=0;
            while(j<tamanhoTexto && SR[j]!="\0" && SR[j]!=palavra) j++;
            SR[j] = palavra;
        }

        /*atualiza menores palavras com mais vogais sem repetição*/
        if(valor.nVD(palavra, valor.nLetras)>nVogaisVD){
            int j=0;
            nVogaisVD = valor.nVD(palavra, valor.nLetras);
            tamanhoVD = valor.nLetras;
            while(j<tamanhoTexto && VD[j]!="\0"){
                VD[j] = "\0";
                j++;
            }
            VD[0] = palavra;
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras<tamanhoVD){
            int j=0;
            tamanhoVD = valor.nLetras;
            while(j<tamanhoTexto && VD[j]!="\0"){
                VD[j] = "\0";
                j++;
            }
            VD[0] = palavra;
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras==tamanhoVD){
            int j=0;
            while(j<tamanhoTexto && VD[j]!="\0" && VD[j]!=palavra) j++;
            VD[j] = palavra;
        }
    }
    

    /* consultas / queries */
    int Q;
    char * query = new char[3];
    cin >> Q;
    while(Q>0){
        cin >> query;
        int i=0;

        if(strcmp(query, "F")==0){
            while(i<tamanhoTexto && maisFrequentes[i]!="\0"){
                cout << maisFrequentes[i] << " ";
                i++;
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
            while(i<tamanhoTexto && maisLongas[i]!="\0"){
                cout << maisLongas[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "SR")==0){
            while(i<tamanhoTexto && SR[i]!="\0"){
                cout << SR[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "VD")==0){
            while(i<tamanhoTexto && VD[i]!="\0"){
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
    Key maisFrequentes[tamanhoTexto], maisLongas[tamanhoTexto], SR[tamanhoTexto], VD[tamanhoTexto];
    int nOcorrenciasMaisFreq=0, tamanhoMaisLonga=0, tamanhoSR=0, tamanhoVD=INT_MAX, nVogaisVD=-1;

    /*inicializa os vetores de consultas*/
    for(int i=0; i<tamanhoTexto; i++){
        Key nula;
        nula = "\0";
        maisFrequentes[i] = nula;
        maisLongas[i] = nula;
        SR[i] = nula;
        VD[i] = nula;
    }

    for(int i=0; i<tamanhoTexto; i++){
        cin >> palavra;
        //palavra = corrigePalavra(palavra);
        valor = valor.inicializa(palavra);
        Treap.add(palavra, valor);


        /* atualiza os vetores de consultas */
        /*atualiza mais frequentes*/
        if(Treap.value(palavra).nOcorrencias > nOcorrenciasMaisFreq){
            int j=0;
            nOcorrenciasMaisFreq = Treap.value(palavra).nOcorrencias; 
            while(j<tamanhoTexto && maisFrequentes[j]!="\0"){
                maisFrequentes[j] = "\0";
                j++;
            }
            maisFrequentes[0] = palavra;
        }
        else if(Treap.value(palavra).nOcorrencias == nOcorrenciasMaisFreq){
            int j=0;
            while(j<tamanhoTexto && maisFrequentes[j]!="\0" && maisFrequentes[j]!=palavra) j++;
            maisFrequentes[j] = palavra;
        }

        /*atualiza mais longas*/
        if(valor.nLetras > tamanhoMaisLonga){
            int j=0;
            tamanhoMaisLonga = valor.nLetras;
            while(j<tamanhoTexto && maisLongas[j]!="\0"){
                maisLongas[j] = "\0";
                j++;
            }
            maisLongas[0] = palavra;
        }
        else if(valor.nLetras == tamanhoMaisLonga){
            int j=0;
            while(j<tamanhoTexto && maisLongas[j]!="\0" && maisLongas[j]!=palavra) j++;
            maisLongas[j] = palavra;
        }

        /*atualiza maiores palavras que nao repetem letras*/
        if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras>tamanhoSR){
            int j=0;
            tamanhoSR = valor.nLetras;
            while(j<tamanhoTexto && SR[j]!="\0"){
                SR[j] = "\0";
                j++;
            }
            SR[0] = palavra;
        }
        else if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras==tamanhoSR){
            int j=0;
            while(j<tamanhoTexto && SR[j]!="\0" && SR[j]!=palavra) j++;
            SR[j] = palavra;
        }

        /*atualiza menores palavras com mais vogais sem repetição*/
        if(valor.nVD(palavra, valor.nLetras)>nVogaisVD){
            int j=0;
            nVogaisVD = valor.nVD(palavra, valor.nLetras);
            tamanhoVD = valor.nLetras;
            while(j<tamanhoTexto && VD[j]!="\0"){
                VD[j] = "\0";
                j++;
            }
            VD[0] = palavra;
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras<tamanhoVD){
            int j=0;
            tamanhoVD = valor.nLetras;
            while(j<tamanhoTexto && VD[j]!="\0"){
                VD[j] = "\0";
                j++;
            }
            VD[0] = palavra;
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras==tamanhoVD){
            int j=0;
            while(j<tamanhoTexto && VD[j]!="\0" && VD[j]!=palavra) j++;
            VD[j] = palavra;
        }
    }
    

    /* consultas / queries */
    int Q;
    char * query = new char[3];
    cin >> Q;
    while(Q>0){
        cin >> query;
        int i=0;

        if(strcmp(query, "F")==0){
            while(i<tamanhoTexto && maisFrequentes[i]!="\0"){
                cout << maisFrequentes[i] << " ";
                i++;
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
            while(i<tamanhoTexto && maisLongas[i]!="\0"){
                cout << maisLongas[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "SR")==0){
            while(i<tamanhoTexto && SR[i]!="\0"){
                cout << SR[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "VD")==0){
            while(i<tamanhoTexto && VD[i]!="\0"){
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
    Key maisFrequentes[tamanhoTexto], maisLongas[tamanhoTexto], SR[tamanhoTexto], VD[tamanhoTexto];
    int nOcorrenciasMaisFreq=0, tamanhoMaisLonga=0, tamanhoSR=0, tamanhoVD=INT_MAX, nVogaisVD=-1;

    /*inicializa os vetores de consultas*/
    for(int i=0; i<tamanhoTexto; i++){
        Key nula;
        nula = "\0";
        maisFrequentes[i] = nula;
        maisLongas[i] = nula;
        SR[i] = nula;
        VD[i] = nula;
    }

    for(int i=0; i<tamanhoTexto; i++){
        cin >> palavra;
        //palavra = corrigePalavra(palavra);
        valor = valor.inicializa(palavra);
        Arvore23.add(palavra, valor);


        /* atualiza os vetores de consultas */
        /*atualiza mais frequentes*/
        if(Arvore23.value(palavra).nOcorrencias > nOcorrenciasMaisFreq){
            int j=0;
            nOcorrenciasMaisFreq = Arvore23.value(palavra).nOcorrencias; 
            while(j<tamanhoTexto && maisFrequentes[j]!="\0"){
                maisFrequentes[j] = "\0";
                j++;
            }
            maisFrequentes[0] = palavra;
        }
        else if(Arvore23.value(palavra).nOcorrencias == nOcorrenciasMaisFreq){
            int j=0;
            while(j<tamanhoTexto && maisFrequentes[j]!="\0" && maisFrequentes[j]!=palavra) j++;
            maisFrequentes[j] = palavra;
        }

        /*atualiza mais longas*/
        if(valor.nLetras > tamanhoMaisLonga){
            int j=0;
            tamanhoMaisLonga = valor.nLetras;
            while(j<tamanhoTexto && maisLongas[j]!="\0"){
                maisLongas[j] = "\0";
                j++;
            }
            maisLongas[0] = palavra;
        }
        else if(valor.nLetras == tamanhoMaisLonga){
            int j=0;
            while(j<tamanhoTexto && maisLongas[j]!="\0" && maisLongas[j]!=palavra) j++;
            maisLongas[j] = palavra;
        }

        /*atualiza maiores palavras que nao repetem letras*/
        if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras>tamanhoSR){
            int j=0;
            tamanhoSR = valor.nLetras;
            while(j<tamanhoTexto && SR[j]!="\0"){
                SR[j] = "\0";
                j++;
            }
            SR[0] = palavra;
        }
        else if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras==tamanhoSR){
            int j=0;
            while(j<tamanhoTexto && SR[j]!="\0" && SR[j]!=palavra) j++;
            SR[j] = palavra;
        }

        /*atualiza menores palavras com mais vogais sem repetição*/
        if(valor.nVD(palavra, valor.nLetras)>nVogaisVD){
            int j=0;
            nVogaisVD = valor.nVD(palavra, valor.nLetras);
            tamanhoVD = valor.nLetras;
            while(j<tamanhoTexto && VD[j]!="\0"){
                VD[j] = "\0";
                j++;
            }
            VD[0] = palavra;
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras<tamanhoVD){
            int j=0;
            tamanhoVD = valor.nLetras;
            while(j<tamanhoTexto && VD[j]!="\0"){
                VD[j] = "\0";
                j++;
            }
            VD[0] = palavra;
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras==tamanhoVD){
            int j=0;
            while(j<tamanhoTexto && VD[j]!="\0" && VD[j]!=palavra) j++;
            VD[j] = palavra;
        }
    }
    

    /* consultas / queries */
    int Q;
    char * query = new char[3];
    cin >> Q;
    while(Q>0){
        cin >> query;
        int i=0;

        if(strcmp(query, "F")==0){
            while(i<tamanhoTexto && maisFrequentes[i]!="\0"){
                cout << maisFrequentes[i] << " ";
                i++;
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
            while(i<tamanhoTexto && maisLongas[i]!="\0"){
                cout << maisLongas[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "SR")==0){
            while(i<tamanhoTexto && SR[i]!="\0"){
                cout << SR[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "VD")==0){
            while(i<tamanhoTexto && VD[i]!="\0"){
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
    Key maisFrequentes[tamanhoTexto], maisLongas[tamanhoTexto], SR[tamanhoTexto], VD[tamanhoTexto];
    int nOcorrenciasMaisFreq=0, tamanhoMaisLonga=0, tamanhoSR=0, tamanhoVD=INT_MAX, nVogaisVD=-1;

    /*inicializa os vetores de consultas*/
    for(int i=0; i<tamanhoTexto; i++){
        Key nula;
        nula = "\0";
        maisFrequentes[i] = nula;
        maisLongas[i] = nula;
        SR[i] = nula;
        VD[i] = nula;
    }

    for(int i=0; i<tamanhoTexto; i++){
        cin >> palavra;
        //palavra = corrigePalavra(palavra);
        valor = valor.inicializa(palavra);
        ArvoreRN.add(palavra, valor);


        /* atualiza os vetores de consultas */
        /*atualiza mais frequentes*/
        if(ArvoreRN.value(palavra).nOcorrencias > nOcorrenciasMaisFreq){
            int j=0;
            nOcorrenciasMaisFreq = ArvoreRN.value(palavra).nOcorrencias; 
            while(j<tamanhoTexto && maisFrequentes[j]!="\0"){
                maisFrequentes[j] = "\0";
                j++;
            }
            maisFrequentes[0] = palavra;
        }
        else if(ArvoreRN.value(palavra).nOcorrencias == nOcorrenciasMaisFreq){
            int j=0;
            while(j<tamanhoTexto && maisFrequentes[j]!="\0" && maisFrequentes[j]!=palavra) j++;
            maisFrequentes[j] = palavra;
        }

        /*atualiza mais longas*/
        if(valor.nLetras > tamanhoMaisLonga){
            int j=0;
            tamanhoMaisLonga = valor.nLetras;
            while(j<tamanhoTexto && maisLongas[j]!="\0"){
                maisLongas[j] = "\0";
                j++;
            }
            maisLongas[0] = palavra;
        }
        else if(valor.nLetras == tamanhoMaisLonga){
            int j=0;
            while(j<tamanhoTexto && maisLongas[j]!="\0" && maisLongas[j]!=palavra) j++;
            maisLongas[j] = palavra;
        }

        /*atualiza maiores palavras que nao repetem letras*/
        if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras>tamanhoSR){
            int j=0;
            tamanhoSR = valor.nLetras;
            while(j<tamanhoTexto && SR[j]!="\0"){
                SR[j] = "\0";
                j++;
            }
            SR[0] = palavra;
        }
        else if(valor.verificaSR(palavra, valor.nLetras) && valor.nLetras==tamanhoSR){
            int j=0;
            while(j<tamanhoTexto && SR[j]!="\0" && SR[j]!=palavra) j++;
            SR[j] = palavra;
        }

        /*atualiza menores palavras com mais vogais sem repetição*/
        if(valor.nVD(palavra, valor.nLetras)>nVogaisVD){
            int j=0;
            nVogaisVD = valor.nVD(palavra, valor.nLetras);
            tamanhoVD = valor.nLetras;
            while(j<tamanhoTexto && VD[j]!="\0"){
                VD[j] = "\0";
                j++;
            }
            VD[0] = palavra;
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras<tamanhoVD){
            int j=0;
            tamanhoVD = valor.nLetras;
            while(j<tamanhoTexto && VD[j]!="\0"){
                VD[j] = "\0";
                j++;
            }
            VD[0] = palavra;
        }
        else if(valor.nVD(palavra, valor.nLetras)==nVogaisVD && valor.nLetras==tamanhoVD){
            int j=0;
            while(j<tamanhoTexto && VD[j]!="\0" && VD[j]!=palavra) j++;
            VD[j] = palavra;
        }
    }
    

    /* consultas / queries */
    int Q;
    char * query = new char[3];
    cin >> Q;
    while(Q>0){
        cin >> query;
        int i=0;

        if(strcmp(query, "F")==0){
            while(i<tamanhoTexto && maisFrequentes[i]!="\0"){
                cout << maisFrequentes[i] << " ";
                i++;
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
            while(i<tamanhoTexto && maisLongas[i]!="\0"){
                cout << maisLongas[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "SR")==0){
            while(i<tamanhoTexto && SR[i]!="\0"){
                cout << SR[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else if(strcmp(query, "VD")==0){
            while(i<tamanhoTexto && VD[i]!="\0"){
                cout << VD[i] << " ";
                i++;
            }
            cout << endl;
            Q--;
        }

        else cout << "Consulta invalida!\n";
    }
}