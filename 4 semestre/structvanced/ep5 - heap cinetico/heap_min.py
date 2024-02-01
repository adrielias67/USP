import numpy as np

class certificado:
    def __init__(self, i, t):
        self.i = i
        self.t = t



def interseccao(no1, no2, t):
    # chave1 sempre menor que chave2
    if no1.v <= no2.v:
        return np.inf
    t_interseccao = (no1.x0 - no2.x0) / (no2.v - no1.v)
    if t_interseccao > t:
        return t_interseccao
    else:
        return np.inf
        



class Hmin:
    heap = []
    n = 0
    V = {}    # guarda a posição no heap do certificado com self.i = i


    def __init__(self, certificados):
        self.heap = []
        self.n = 0
        for certificado in certificados:
            pos = self.insere(certificado)
            self.V[certificado.i] = pos


    def pai(self, i):
        return self.heap[(i-1)//2]
    

    def esq(self, i):
        return self.heap[2*i + 1]
    

    def dir(self, i):
        return self.heap[2*i + 2]
    

    def troca(self, i, j):
        aux = self.heap[i]
        self.heap[i] = self.heap[j]
        self.heap[j] = aux
        #corrige o mapa V
        self.V[self.heap[i].i] = i
        self.V[self.heap[j].i] = j
    

    def min(self):
        return self.heap[0]
    

    def insere(self, certificado):
        # Só é utilizado na construção do heap, não na inserção de novos elementos
        self.heap.append(certificado)
        self.n += 1
        i = self.n - 1
        while i > 0 and self.pai(i).t > self.heap[i].t:
            self.troca(i, (i-1)//2)
            i = (i-1)//2
        return i


    def update(self, i, H, now, modo):
        # Da update em Q, no certificado de i com pai(i) em H
        if i >= H.n:
            return
        filho = H.heap[i]
        pai = H.pai(i)
        if modo==0:
            certificado_novo = certificado(i, interseccao(filho, pai, now))
        if modo==1:
            certificado_novo = certificado(i, now)
        pos = self.V[i]
        self.heap[pos] = certificado_novo

        # corrige subindo
        while pos > 0 and self.pai(pos).t > self.heap[pos].t:
            self.troca(pos, (pos-1)//2)
            pos = (pos-1)//2
            
        # corrige descendo
        stop = False
        while not stop:
            #tem 2 filhos
            if 2*pos+2 < self.n:
                esq = self.esq(pos)
                dir = self.dir(pos)
                if esq.t < dir.t:
                    if esq.t < self.heap[pos].t:
                        self.troca(pos, 2*pos+1)
                        pos = 2*pos+1
                    else:
                        stop = True
                elif dir.t < self.heap[pos].t:
                        self.troca(pos, 2*pos+2)
                        pos = 2*pos+2
                else:
                    stop = True
            #só filho esquerdo
            elif 2*pos+1 < self.n:
                if self.esq(pos).t < self.heap[pos].t:
                    self.troca(pos, 2*pos+1)
                    pos = 2*pos+1
                else:
                    stop = True
            #não tem filhos
            else:
                stop = True