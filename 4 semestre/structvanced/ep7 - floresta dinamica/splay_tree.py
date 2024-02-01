class no_st:
    def __init__(self, val):
        self.eh_raiz = False
        self.nos = 1
        self.val = val
        self.esq = None
        self.dir = None
        self.pai = None



def _roda_esq(no):
    aux = no.dir
    no.dir = aux.esq
    if no.dir!=None:
        no.dir.pai = no
    aux.esq = no
    aux.pai = no.pai
    no.pai = aux
    no.nos = _qtd_nos(no)
    aux.nos = _qtd_nos(aux)
    if aux.pai!=None:
        aux.pai.nos = _qtd_nos(aux.pai)
    return aux


def _roda_dir(no):
    aux = no.esq
    no.esq = aux.dir
    if no.esq!=None:
        no.esq.pai = no
    aux.dir = no
    aux.pai = no.pai
    no.pai = aux
    no.nos = _qtd_nos(no)
    aux.nos = _qtd_nos(aux)
    if aux.pai!=None:
        aux.pai.nos = _qtd_nos(aux.pai)
    return aux

def _qtd_nos(no):
    # Calcula a quantidade de nós na subárvore
    if no==None:
        return 0
    q = 1
    if no.esq!=None:
        q += no.esq.nos
    if no.dir!=None:
        q += no.dir.nos
    return q


def _splay_step(no, x):
    # Da splay em x, na range dos 2 níveis abaixo de no
    if no==None:
        return None

    if no.esq==None and no.dir==None:
        return no

    if no.esq!=None:
        if no.esq.val==x:
            # caso da raíz
            if no.eh_raiz==True:
                no.eh_raiz = False
                pai = _roda_dir(no)
                return pai
            else:
                return no
        elif no.esq.esq!=None and no.esq.esq.val==x:
            # caso da val na esquerda da esquerda
            pai = _roda_dir(no)
            paipai = _roda_dir(pai)
            if no.eh_raiz==True:
                no.eh_raiz = False
            return paipai
        elif no.esq.dir!=None and no.esq.dir.val==x:
            # caso da val na direita da esquerda
            no.esq = _roda_esq(no.esq)
            pai = _roda_dir(no)
            if no.eh_raiz==True:
                no.eh_raiz = False
            return pai

    if no.dir!=None:
        if no.dir.val==x:
            # caso da raíz
            if no.eh_raiz==True:
                no.eh_raiz = False
                pai = _roda_esq(no)
                return pai
            else:
                return no
        elif no.dir.dir!=None and no.dir.dir.val==x:
            # caso da val na direita da direita
            pai = _roda_esq(no)
            paipai = _roda_esq(pai)
            if no.eh_raiz==True:
                no.eh_raiz = False
            return paipai
        elif no.dir.esq!=None and no.dir.esq.val==x:
            # caso da val na esquerda da direita
            no.dir = _roda_dir(no.dir)
            pai = _roda_esq(no)
            if no.eh_raiz==True:
                no.eh_raiz = False
            return pai


def _insertR(no, x):
    # Insere x recursivamente e dá splay nele
    if no==None:
        novo = no_st(x)
        return novo
    
    elif x < no.val:
        no.esq = _insertR(no.esq, x)
        no.esq.pai = no
        no.nos = _qtd_nos(no)
        pai = _splay_step(no, x)
        return pai
    else:
        no.dir = _insertR(no.dir, x)
        no.dir.pai = no
        no.nos = _qtd_nos(no)
        pai = _splay_step(no, x)
        return pai


val_splay = None


def _troca_deleteR(no):
    # Função para trocar o nó a ser deletado com o menor nó da subárvore direita
    if no.esq.esq==None:
        aux = no.esq
        no.esq = None # já deleta o nó
        no.nos = _qtd_nos(no)
        return aux
    else:
        ret = _troca_deleteR(no.esq)
        no.nos = _qtd_nos(no)
        return ret


def _deleteR(no, x):
    # Troca o nó para uma folha, deleta e dá splay no pai dele
    if no.esq==None and no.dir==None:
        # caso nó folha
        if no.val==x:
            return None
        else:
            return no

    if no.val==x:
        if no.esq==None:
            # caso em que não tem filho esquerdo
            pai = _roda_esq(no)
            pai.esq = _deleteR(pai.esq, x)
            pai.nos = _qtd_nos(pai)
            global val_splay
            val_splay = pai.val
            return pai
        elif no.dir==None:
            # caso em que não tem filho direito
            pai = _roda_dir(no)
            pai.dir = _deleteR(pai.dir, x)
            pai.nos = _qtd_nos(pai)
            val_splay = pai.val
            return pai
        else:
            if no.dir.esq==None:
                # caso em que só tem um filho direito
                no.val = no.dir.val
                no.dir = None
                no.nos = _qtd_nos(no)
                val_splay = no.val
                return no
            else:
                # caso da troca com o menor nó da subárvore direita
                aux = no
                no = _troca_deleteR(no.dir)
                no.esq = aux.esq
                no.dir = aux.dir
                no.nos = _qtd_nos(no)
                val_splay = no.val
                return no

    else:
        if no.esq!=None and no.esq.val==x and no.esq.esq==None and no.esq.dir==None:
            # caso folha
            no.esq = _deleteR(no.esq, x)
            val_splay = no.val
            no.nos = _qtd_nos(no)
            return no
        if no.dir!=None and no.dir.val==x and no.dir.esq==None and no.dir.dir==None:
            # caso folha
            no.dir = _deleteR(no.dir, x)
            val_splay = no.val
            no.nos = _qtd_nos(no)
            return no
        elif x < no.val:
            # caso recursivo (ainda não chegou no nó a ser deletado)
            no.esq =_deleteR(no.esq, x)
            no.nos = _qtd_nos(no)
            pai = _splay_step(no, val_splay)
            return pai
        else:
            # caso recursivo (ainda não chegou no nó a ser deletado)
            no.dir = _deleteR(no.dir, x)
            no.nos = _qtd_nos(no)
            pai = _splay_step(no, val_splay)
            return pai


def _searchR(no, x):
    # Procura x recursivamente e dá splay nele
    if no==None:
        return None
    
    elif no.val==x:
        return no
    
    else:
        if x < no.val:
            no.esq = _searchR(no.esq, x)
            pai = _splay_step(no, x)
            return pai
        else:
            no.dir = _searchR(no.dir , x)
            pai = _splay_step(no, x)
            return pai


def _minR(no):
    # Retorna o menor nó da árvore e dá splay nele
    if no.esq==None:
        global val_splay
        val_splay = no.val
        return no

    else:
        no.esq = _minR(no.esq)
        pai = _splay_step(no, val_splay)
        return pai


def _printR(no, height):
    if no==None:
        return
    
    _printR(no.esq, height+1)
    for i in range(height):
        print("   ", end="")
    print(no.val)
    # print(no.val,"(", end="")
    # if no.pai!=None: 
    #     print(no.pai.val, end=" ")
    # print(int(no.eh_raiz), ")", sep="")
    _printR(no.dir, height+1)



class ST:
    raiz = None

    def __init__(self):
        return self.raiz
    
    def Insert(self, x):
        self.raiz = _insertR(self.raiz, x)
        self.raiz.eh_raiz = True
        self.raiz.pai = None

    def Delete(self, x):
        self.raiz = _deleteR(self.raiz, x)
        self.raiz.eh_raiz = True
        self.raiz.pai = None

    def Search(self, x):
        self.raiz = _searchR(self.raiz, x)
        self.raiz.eh_raiz = True
        self.raiz.pai = None
        return self.raiz.val==x
    
    def Splay(self, x):
        self.Search(x)

    def Min(self):
        self.raiz = _minR(self.raiz)
        self.raiz.eh_raiz = True
        self.raiz.pai = None
        return self.raiz
    
    def Split(self, x):
        self.Splay(x)
        aux = self.raiz.dir
        aux.eh_raiz = True
        aux.pai = None
        self.raiz.dir = None
        self.raiz.nos -= aux.nos
        nova = ST()
        nova.raiz = aux
        return self, nova

    def Print(self):
        _printR(self.raiz, 0)

def Join(S, T):
    T.Min()
    T.raiz.esq = S.raiz
    S.raiz.eh_raiz = False
    S.raiz.pai = T.raiz
    T.raiz.nos += S.raiz.nos
    return T