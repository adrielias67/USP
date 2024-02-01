import heap_max as hmax
import heap_min as hmin
import numpy as np

def interseccao(no1, no2, t):
    # chave1 sempre menor que chave2
    if no1.v <= no2.v:
        return np.inf
    t_interseccao = (no1.x0 - no2.x0) / (no2.v - no1.v)
    if t_interseccao > t:
        return t_interseccao
    else:
        return np.inf
    

def recalcula(x_now, v, t):
    # Recalcula o x0 baseado no x_now, v, t
    return x_now - v*t


def printR_max(heap, pos, i, now):
        # Print do heap H
        if pos < heap.n:
            #recursao na esquerda
            printR_max(heap, _esq(pos), i+1, now)
            for j in range(i):
                print("   ", end="")
            # formatação para printar inteiro ou float
            x = float(heap.heap[pos].x_now(now))
            if x-int(x) < 0.1:
                print(int(x), end="")
            else:
                print(x, end="")
            print(" (", end="")
            x0 = float(heap.heap[pos].x0)
            if x0-int(x0) < 0.1:
                print(int(x0), end="")
            else:
                print(x0, end="")
            print(" ", end="")
            v = float(heap.heap[pos].v)
            if v-int(v) < 0.1:
                print(int(v), end="")
            else:
                print(v, end="")
            print(")")
            # recursão na direita
            printR_max(heap, _dir(pos), i+1, now)


def printR_min(heap, pos, i):
        # Print do heap Q, para fins de debug
        if pos < heap.n:
            printR_min(heap, 2*pos+1, i+1)
            for j in range(i):
                print("   ", end="")
            print(heap.heap[pos].i, " [", heap.heap[pos].t, "]", sep="")
            printR_min(heap, 2*pos+2, i+1)


def _pai(i):
    return (i-1)//2


def _esq(i):
    return 2*i + 1


def _dir(i):
    return 2*i + 2


def _sibling(i):
    if i%2 == 0:
        return i-1
    else:
        return i+1



class KinHeap:
    V = {}     # mapa de id para no
    n = 0      # número de elementos
    now = 0    # tempo atual
    H = None
    Q = None


    def __init__(self, nos, n):
        # inicializa o mapa V
        for no in nos:
            self.V[no.id] = no
        self.n = n
        now = 0
        
        # inicializa H
        self.H = hmax.Hmax(nos)

        # inicializa Q
        certificados = []
        for i in list(range(1, n)):
            certificado = hmin.certificado(i, interseccao(self.H.heap[i], self.H.pai(i), 0))
            certificados.append(certificado)
        self.Q = hmin.Hmin(certificados)


    def event(self, i):
        self.H.troca(i, _pai(i))
        if i>2:
            self.Q.update(_pai(i), self.H, self.now, 0)
        self.Q.update(i, self.H, self.now, 0)
        if _esq(i) < self.n:
            self.Q.update(_esq(i), self.H, self.now, 0)
        if _dir(i) < self.n:
            self.Q.update(_dir(i), self.H, self.now, 0)
        s = _sibling(i)
        if s>0 and s<self.n:
            self.Q.update(s, self.H, self.now, 0)


    def Advance(self, t):
        while self.Q.min().t <= t:
            now = self.Q.min().t
            self.event(self.Q.min().i)
        self.now = t


    def Change(self, id, v):
        x_now = self.V[id].x_now(self.now)
        self.V[id].x0 = recalcula(x_now, v, self.now)
        self.V[id].v = v
        i = self.H.id2i[id]
        if i>0:
            self.Q.update(i, self.H, self.now, 0)
        if _esq(i) < self.n:
            self.Q.update(_esq(i), self.H, self.now, 0)
        if _dir(i) < self.n:
            self.Q.update(_dir(i), self.H, self.now, 0)


    def Insert(self, id, xnow, v):
        # corrige os dados das estruturas de acordo
        self.n += 1
        self.H.n += 1
        self.Q.n += 1
        x0 = recalcula(xnow, v, self.now)
        i = self.n - 1
        no = hmax.no(i, x0, v)
        self.V[id] = no
        self.H.heap.append(no)
        self.H.id2i[no.id] = i
        self.Q.V[no.id] = i

        # sobe no heap com os events
        if xnow > self.H.heap[_pai(i)].x_now(self.now):
            self.Q.heap.append(hmin.certificado(i, self.now))
        else:
            self.Q.heap.append(hmin.certificado(i, interseccao(self.H.heap[i], self.H.pai(i), self.now)))
        while i>0 and xnow>self.H.heap[_pai(i)].x_now(self.now):
            self.event(i)
            i = _pai(i)
            if i>0 and xnow>self.H.heap[_pai(i)].x_now(self.now):
                self.Q.update(i, self.H, self.now, 1)
            else:
                self.Q.update(i, self.H, self.now, 0)

    def Max(self):
        return self.H.max()


    def DeleteMax(self):
        self.Delete(self.Max().id)


    def Delete(self, id):
        # Leva o elemento para o final do heap e remove 
        # corrige os dados das estruturas de acordo
        i = self.H.id2i[id]
        self.V[id] = None
        self.H.troca(i, self.n-1)    # troca o id deletado com o último 
        self.Q.update(self.n-1, self.H, self.now, 0)
        self.H.heap.pop()
        self.H.n -= 1
        self.n -= 1
        self.H.id2i.pop(id)
        if i>0:
            self.Q.update(i, self.H, self.now, 0)

        # corrige o id trocado em H
        stop = False
        while not stop:
            #tem 2 filhos
            if _dir(i) < self.n:
                esq = self.H.esq(i)
                dir = self.H.dir(i)
                x_esq = esq.x_now(self.now)
                x_dir = dir.x_now(self.now)
                if x_esq > x_dir:
                    if x_esq > self.H.heap[i].x_now(self.now):
                        self.H.troca(i, _esq(i))
                        if i>0:
                            self.Q.update(i, self.H, self.now, 0)
                        self.Q.update(_esq(i), self.H, self.now, 0)
                        self.Q.update(_dir(i), self.H, self.now, 0)
                        self.Q.update(_esq(_esq(i)), self.H, self.now, 0)
                        self.Q.update(_dir(_esq(i)), self.H, self.now, 0)
                        i = _esq(i)
                    else:
                        stop = True
                elif x_dir > self.H.heap[i].x_now(self.now):
                        self.H.troca(i, _dir(i))
                        if i>0:
                            self.Q.update(i, self.H, self.now, 0)
                        self.Q.update(_esq(i), self.H, self.now, 0)
                        self.Q.update(_dir(i), self.H, self.now, 0)
                        self.Q.update(_esq(_dir(i)), self.H, self.now, 0)
                        self.Q.update(_dir(_dir(i)), self.H, self.now, 0)
                        i = _dir(i)
                else:
                    stop = True
            #só filho esquerdo
            elif _esq(i) < self.n:
                if self.H.esq(i).x_now(self.now) > self.heap[i].x_now(self.now):
                    self.troca(i, _esq(i))
                    if i>0:
                        self.Q.update(i, self.H, self.now, 0)
                    self.Q.update(_esq(i), self.H, self.now, 0)
                    self.Q.update(_esq(_esq(i)), self.H, self.now, 0)
                    self.Q.update(_dir(_esq(i)), self.H, self.now, 0)
                    i = _esq(i)
                else:
                    stop = True
            #não tem filhos
            else:
                stop = True
            
        # tira o certificado de Q
        pos = self.Q.V[self.H.n]
        self.Q.troca(pos, self.Q.n-1)
        self.Q.V.pop(self.Q.heap[self.Q.n-1].i)
        self.Q.n -= 1
        self.Q.heap.pop()
        stop = False
        while not stop:
            #tem 2 filhos
            if _dir(pos) < self.Q.n:
                esq = self.Q.esq(pos)
                dir = self.Q.dir(pos)
                if esq.t < dir.t:
                    if esq.t < self.Q.heap[pos].t:
                        self.Q.troca(pos, _esq(pos))
                        pos = _esq(pos)
                    else:
                        stop = True
                elif dir.t < self.Q.heap[pos].t:
                        self.Q.troca(pos, _dir(pos))
                        pos = _dir(pos)
                else:
                    stop = True
            #só filho esquerdo
            elif _esq(pos) < self.Q.n:
                if self.Q.esq(pos).t < self.Q.heap[pos].t:
                    self.Q.troca(pos, _esq(pos))
                    pos = _esq(pos)
                else:
                    stop = True
            #não tem filhos
            else:
                stop = True


    def Print(self):
        # print("H:")
        printR_max(self.H, 0, 0, self.now)
        # print("Q:")
        # printR_min(self.Q, 0, 0)