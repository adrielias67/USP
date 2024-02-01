#include <bits/stdc++.h>
#include <random>
#include "aviao.h"

using namespace std;




// numa pista, o valor int é o tempo restante que ficará interditada
typedef int pista;



default_random_engine gerador;



void sorteiaPouso(char id[], char aeroporto[], int * tempo, bool * emergencia, int CombustivelMax, float probEmergencia){
    // sorteia os dados de um aviao qua vai pousar
    int i;
    
    /* id */
    for(i=0; i<2; i++){
        uniform_int_distribution<int> distrI('a', 'z');
        id[i] = distrI(gerador);
    }
    for(i=2; i<5; i++){
        uniform_int_distribution<int> distrI('0', '9');
        id[i] = distrI(gerador);
    }

    /* aeroporto */
    for(i=0; i<3; i++){
        uniform_int_distribution<int> distrI('a', 'z');
        aeroporto[i] = distrI(gerador);
    }

    /* tempo (combustivel) */
	uniform_int_distribution<int> distrI(1, CombustivelMax);
    * tempo = distrI(gerador);

    /* emergencia */
    bernoulli_distribution distrB(probEmergencia);
    * emergencia = distrB(gerador);
}



void sorteiaDecolagem(char id[], char aeroporto[], int * tempo, bool * emergencia, int VooTempoMax, float probEmergencia){
// sorteia os dados de um aviao qua vai decolar
    int i;

    /* id */
    for(i=0; i<2; i++){
        uniform_int_distribution<int> distrI('a', 'z');
        id[i] = distrI(gerador);
    }
    for(i=2; i<5; i++){
        uniform_int_distribution<int> distrI('0', '9');
        id[i] = distrI(gerador);
    }

    /* aeroporto */
    for(i=0; i<3; i++){
        uniform_int_distribution<int> distrI('a', 'z');
        aeroporto[i] = distrI(gerador);
    }

    /* tempo (de espera) */
	uniform_int_distribution<int> distrI(1, VooTempoMax);
    * tempo = distrI(gerador);
    * tempo = * tempo / 10;

    /* emergencia */
    bernoulli_distribution distrB(probEmergencia);
    * emergencia = distrB(gerador);
}



void imprimeFilas(aviao * FilaPouso, aviao * FilaDecolagem, int iteracao){
    // imprime as tabelas de avioes
    cout << "##########INSTANTE " << iteracao+1 << "##########\n";
        cout << " Avioes na fila de POUSO:\n";
        cout << " IDs     / Aeroporto / Combustivel\n";
        imprimeLista(FilaPouso);
        cout << endl;

        cout << " Avioes na fila de DECOLAGEM:\n";
        cout << " IDs     / Aeroporto / Combustivel\n";
        imprimeLista(FilaDecolagem);
        cout << endl;
}



int main(){
    int i, j, tempoSimulacao, KAvioesNovosMax, CombustivelMax, VooTempoMax, semente,
    tempo, nPistasLivres, somaEsperaPousaram=0, somaEsperaDecolagem=0, somaTempoVoando=0, somaTempoPousaram=0, somaCombustivelPousaram=0, 
    nAvioesVoando=0, nAvioesPousaram=0, nAvioesDecolaram=0, nAvioesEmergencia=0, nEmergenciasTratadas=0;
    float probPouso, probEmergencia;
    bool emergencia;
    char id[5], aeroporto[3];

    aviao * FilaDecolagem = new(aviao);
    aviao * FilaPouso = new(aviao);
    aviao * aux;

    pista pista[3];
    for(i=0; i<3; i++) pista[i] = 0;    // inicializa as pistas

    cout << "Digite T, K, Pp, Pe, C, V, seed: ";
    cin >> tempoSimulacao >> KAvioesNovosMax >> probPouso >> probEmergencia >> CombustivelMax >> VooTempoMax >> semente;
    cout << "\n\n\n";

    random_device seed;
    if(semente==0){
        auto s = seed();
	    gerador = default_random_engine(s);
    }
    else gerador = default_random_engine(semente);


    for(i=0; i<tempoSimulacao; i++){
        /// SIMULAÇÃO ///


        /* atualiza o tempo das pistas interditadas */
        nPistasLivres = 3;
        for(j=0; j<3; j++){
            pista[j] = max(0, pista[j]-1);
            if(pista[j]!=0) nPistasLivres--;
        }


        /* atualiza os tempos das filas */
        update(FilaDecolagem);
        update(FilaPouso);


        /* sorteia K aviões novos no instante novo */
        uniform_int_distribution<int> distrI(0, KAvioesNovosMax);
        j = distrI(gerador);

        while(j--){
            bernoulli_distribution distrI(probPouso);       // sorteia se é pouso ou decolagem
            if(distrI(gerador)){
                // pouso
                sorteiaPouso(id, aeroporto, &tempo, &emergencia, CombustivelMax, probEmergencia);
                FilaPouso = inicializa(FilaPouso, id, aeroporto, tempo, emergencia);
            }
            else{
                // decolagem
                sorteiaDecolagem(id, aeroporto, &tempo, &emergencia, VooTempoMax, probEmergencia);
                FilaDecolagem = inicializa(FilaDecolagem, id, aeroporto, tempo, emergencia);
            }
        }


        /* imprime as filas */
        imprimeFilas(FilaPouso, FilaDecolagem, i);
        cout << " Tempo restante de interditação das pistas: " << pista[0] << "/" << pista[1] << "/" << pista[2] << endl;
        

        /* prioriza as emergências */
        if(nPistasLivres>0){
            while(!filaVazia(FilaPouso) && FilaPouso->emergencia){
                for(j=0; j<3; j++){
                    if(pista[j]==0){
                        pista[j] = 3;
                        nEmergenciasTratadas++;
                        somaEsperaPousaram += FilaPouso->tempoEspera;
                        somaCombustivelPousaram += FilaPouso->tempo;
                        nAvioesPousaram++;
                        FilaPouso = removeInicio(FilaPouso);
                        nPistasLivres--;
                        break;
                    }
                }
                if(nPistasLivres==0) break;     // todas pistas interditadas
            }

            while(!filaVazia(FilaDecolagem) && FilaDecolagem->emergencia){
                for(j=2; j>=0; j--){
                    if(pista[j]==0){
                        pista[j] = 3;
                        nEmergenciasTratadas++;
                        somaEsperaDecolagem += FilaDecolagem->tempoEspera;
                        nAvioesDecolaram++;
                        FilaDecolagem = removeInicio(FilaDecolagem);
                        nPistasLivres--;
                        break;
                    }
                }
                if(nPistasLivres==0) break;     // todas pistas interditadas
            }
        }


        /* coloca os aviões das filas nas pistas */
        if(nPistasLivres>0){
            while(!filaVazia(FilaPouso)){
                if(FilaPouso->tempo<3 || nPistasLivres>1){
                    for(j=0; j<3; j++){
                        if(pista[j]==0){
                            pista[j] = 3;
                            somaEsperaPousaram += FilaPouso->tempoEspera;
                            somaCombustivelPousaram += FilaPouso->tempo;
                            nAvioesPousaram++;
                            FilaPouso = removeInicio(FilaPouso);
                            nPistasLivres--;
                            break;
                        }
                    }
                }
                else break;
                if(nPistasLivres==0) break;
            }

            while(!filaVazia(FilaDecolagem)){
                if(FilaDecolagem->tempo<3 || nPistasLivres>1){
                    for(j=2; j>=0; j--){
                        if(pista[j]==0){
                            pista[j] = 3;
                            nAvioesDecolaram++;
                            somaEsperaDecolagem += FilaDecolagem->tempoEspera;
                            FilaDecolagem = removeInicio(FilaDecolagem);                          
                            nPistasLivres--;
                            break;
                        }
                    }
                }
                else break;
                if(nPistasLivres==0) break;
            }
        }
        
        
        /* manda para outro aeroporto aviões com 1 de combustível */
        if(!filaVazia(FilaPouso) && nPistasLivres==0){
            while(FilaPouso->tempo==1){
                cout << " desvio de aeroporto (" << FilaPouso->id << ")\n";
                FilaPouso = removeInicio(FilaPouso);
                if(filaVazia(FilaPouso)) break;
            }
            aux = FilaPouso;
            while(aux->prox!=nullptr && aux->prox->emergencia) aux = aux->prox;
            while(aux->prox!=nullptr && aux->prox->tempo==1){
                cout << " desvio de aeroporto (" << aux->prox->id << ")\n";
                removeProx(aux);
            }
        }


        /* cancela voos que superaram 10% do tempo de voo */
        if(!filaVazia(FilaDecolagem) && nPistasLivres==0){
            while(FilaDecolagem->tempo==0){
                cout << " voo cancelado (" << FilaDecolagem->id << ")\n";
                FilaDecolagem = removeInicio(FilaDecolagem);
                if(filaVazia(FilaDecolagem)) break;
            }
            aux = FilaDecolagem;
            while(aux->prox!=nullptr && aux->prox->emergencia) aux = aux->prox;
            while(aux->prox!=nullptr && aux->prox->tempo==0){
                cout << " voo cancelado (" << aux->prox->id << ")\n";
                removeProx(aux);
            }
        }

        cout << endl;
        cout << " Tempo medio de espera para pouso: " << (float) somaEsperaPousaram / nAvioesPousaram;
        cout << "  ||  Tempo medio de espera para decolagem: " << (float) somaEsperaDecolagem / nAvioesDecolaram << endl;
        cout << " Quantidade media de combustivel dos avioes esperando para pousar: " << (float) somaTempo(FilaPouso) / tamanho(FilaPouso) << endl;
        cout << " Quantidade media de combustivel dos avioes que pousaram: " << (float) somaCombustivelPousaram / nAvioesPousaram << endl;
        cout << " Quantidade de avioes pousando/decolando em emergencia: " << nEmergenciasTratadas << endl;
        cout << "###############################" << endl;

        nEmergenciasTratadas=0;
        cout << "\n\n";
        //sleep(1);
    }

    exit(0);
}