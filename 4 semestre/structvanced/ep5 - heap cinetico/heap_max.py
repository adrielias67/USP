class no:
    def __init__(self, id, x0, v):
        self.id = id
        self.x0 = x0
        self.v = v


    def x_now(self, now):
        return self.x0 + self.v * now



class Hmax:
    heap = []
    id2i = {}    # guarda a posição no heap de acordo com o id
    n = 0


    def __init__(self, nos):
        self.heap = []
        self.n = 0
        for no in nos:
            pos = self.insere(no)
            self.id2i[no.id] = pos



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
        #corrige o mapa id2i
        self.id2i[self.heap[i].id] = i
        self.id2i[self.heap[j].id] = j
    

    def max(self):
        return self.heap[0]
    

    def insere(self, no):
        # Só é utilizado na construção do heap, não na inserção de novos elementos
        self.heap.append(no)
        self.n += 1
        i = self.n - 1
        while i > 0 and self.pai(i).x0 < self.heap[i].x0:
            self.troca(i, (i-1)//2)
            i = (i-1)//2
        return i
        