class stack:
    def __init__(self):
        self.stack = []
    
    def push(self, item):
        self.stack.append(item)
    
    def pop(self):
        return self.stack.pop()
    
    def top(self):
        return self.stack[-1]
    
    def empty(self):
        return len(self.stack)==0
    
    def size(self):
        return len(self.stack)
    



class node:
    def __init__(self, index, start, end):
        self.index = index
        self.start = start
        self.end = end

class Bnode:
    def __init__(self, n):
        self.is_leave = False
        self.nodes = [n]
        self.children = [None, None]
    
    def insert_append(self, n):
        self.nodes.append(n)
        self.children.append(None)
    
    def insert_child_mid(self, n):
        aux = self.children[-1]
        self.children[-1] = n
        last = n
        while last.children[-1] != None:
            last = last.children[-1] 
        last.children[-1] = aux

    def insert_child(self, n):
        for i in range(self.size()+1):
            if self.children[i] == None:
                self.children[i] = n
                return
            
    def index(self):
        return self.nodes[0].index
    
    def size(self):
        return len(self.nodes)
    
    def print_AC(self, max_depth):
        print_AC_rec(self, 0, max_depth)


def build_LCP(S):
    LCP = [0]*len(S)
    for i in range(1, len(S)):
        A = S[i-1]
        B = S[i]
        j=0
        while j < len(A) and j < len(B) and A[j]==B[j]:
            j += 1
        LCP[i] = j
    return LCP


def build_AC(LCP):
    # Monta o esqueleto a árvore cartesiana a partir do vetor LCP
    Sac = stack()
    Sac.push(Bnode(node(0, None, None)))

    # monta a árvore cartesiana em O(n) com pilha
    i = 2
    while i < len(LCP):
        print("##################################")
        for i in range(Sac.size()):
            Sac.stack[i].print_AC(4)
            print("-----------------------------")
        print("##################################")
        if LCP[i] > Sac.top().index():
            Sac.push(Bnode(node(LCP[i], None, None)))
            i += 1
        elif LCP[i] == Sac.top().index():
            Sac.top().insert_append(node(LCP[i], None, None))
            i += 1
        else:
            n = Sac.pop()
            if LCP[i] == Sac.top().index():
                Sac.top().insert_child_mid(n)
            else:
                new = Bnode(node(LCP[i], None, None))
                new.insert_child(n)
                i += 1
                Sac.push(new)
            while LCP[i] < Sac.top().index():
                n = Sac.pop()
                if LCP[i] == Sac.top().index():
                    Sac.top().insert_child_mid(n)
                else:
                    new.insert_child(n)
                    i += 1
                    Sac.push(new)

    # o último nó o LCP pode não ser 0, precisamos colocar na AC
    if Sac.size() > 1:
        n = Sac.pop()
        Sac.top().insert_child(n)
    
    return Sac.pop()


def fill_AC(AC, T, SA):
    # Preenche os nós da árvore cartesiana
    global j
    j = 0
    put_leaves_rec(AC, SA)
    start_end_rec(AC, T, 0)       


j = 0
def put_leaves_rec(AC, SA):
    # Preenche as folhas da árvore cartesiana recursivamente
    global j
    if AC==None:
        AC = Bnode(node(SA[j], None, None))
        AC.is_leave = True
        j += 1
        return AC

    for i in range(AC.size()+1):
        AC.children[i] = put_leaves_rec(AC.children[i], SA)
    
    return AC


def start_end_rec(AC, T, spelled_dad):
    # Preenche o start e end dos nós recursivamente
    if AC==None:
        return
    start_end_rec(AC.children[0], T, AC.index())

    if AC.is_leave:
        AC.nodes[0].start = AC.index() + spelled_dad
        AC.nodes[0].end = len(T)-1
        return
    
    for i in range(1, AC.size()+1):
        start_end_rec(AC.children[i], T, AC.index())
        AC.nodes[i-1].end = AC.children[1].nodes[0].start - 1
        AC.nodes[i-1].start = AC.nodes[i-1].end - (AC.index() - spelled_dad - 1)


def print_AC_rec(AC, height, max_depth):
    if AC==None:
        return
    for i in range(AC.size()+1):
        print_AC_rec(AC.children[i], height+1, max_depth)
        if i < AC.size():
            for j in range(max_depth - height):
                print("   ", end="")
            print(AC.index())
            #print(AC.nodes[i].start, AC.nodes[i].end)
            print()




class ASnode:
    def __init__(self):
        self.children = {}
        self.index = None    # só folha tem index
        self.start = None
        self.end = None
        self.k = None        # quantas letras já foram soletradas até esse nó
        self.n_leaves = 0
    
    def insert_child(self, word, node):
        self.children[word[:1]] = node

    def n_children(self):
        return len(self.children)

    def print_AS(self, AS, T):
        print_AS_rec(AS, -1, "", T)


def build_AS(AC, S):
    # Monta a árvore de sufixos a partir da árvore cartesiana
    global j
    j = 0
    return build_AS_rec(AC, S)

def build_AS_rec(AC, S):
    # Monta a árvore de sufixos a partir da árvore cartesiana recursivamente
    global j
    if AC==None:
        return None
    
    AS = ASnode()
    AS.start = AC.nodes[0].start
    AS.end = AC.nodes[0].end

    if AC.is_leave:
        AS.index = AC.index()
        AS.k = len(S[j])
        j += 1
        AS.n_leaves = 1
        return AS
    else:
        AS.k = AC.index()

    for i in range(AC.size()+1):
        if j == len(S): break
        #print(AS.k, S[j])
        letter = S[j][AS.k]
        AS.insert_child(letter, build_AS_rec(AC.children[i], S))
        AS.n_leaves += AS.children[letter].n_leaves

    return AS


def print_AS_rec(AS, height, spelled, T):
    if AS==None:
        return
    
    for _ in range(height): 
        print("   ", end="")

    if AS.n_children() == 0:
        print(spelled, end=" ")
        print(AS.index)
    else:
        print(spelled)
    
    for letter in AS.children:
        child = AS.children[letter]
        print_AS_rec(child, height+1, T[child.start : child.end+1], T)




class AS:
    T = []
    S = []
    SA = {}
    AS = None


    def __init__(self, T):
        T = T + "$"
        self.T = T
        
        inv = {}
        for i in range(len(T)):
            self.S.append(T[i:])
            inv[self.S[i]] = i
        self.S.sort()

        for i in range(len(self.S)):
            self.SA[i] = inv[self.S[i]]
        
        self.LCP = build_LCP(self.S)
    

    def VS_AS(self, SA=None, LCP=None):
        # Monta a árvore de sufixos a partir do vetor de sufixos e LCP
        if SA==None:
            SA = self.SA
        if LCP==None:
            LCP = self.LCP
        print(LCP)
        AC = build_AC(self.LCP)
        AC.print_AC(4)
        fill_AC(AC, self.T, self.SA)
        self.AS = build_AS(AC, self.S)


    def _search_interval(self, P):
        # Devolve a subárvore que contém o intervalo
        return self._search_interval_rec(self.AS, P)

    def _search_interval_rec(self, AS, P):
        # Procura recursivamente a subárvore que contém o intervalo
        if AS == None:
            return None

        if P[:1] in AS.children:
            child = AS.children[P[:1]]
            word = self.T[child.start : child.end+1]
        else:
            return None
        
        for i in range(len(P)):
            if i==len(word):
                return self._search_interval_rec(AS.children[word[:1]], P[len(word):])
            if P[i] != word[i]:
                return None
        return AS.children[word[:1]]


    def Search(self, P):
        if self._search_interval(P) == None:
            return False
        return True
                
    
    def Occurences(self, P):
        AS = self._search_interval(P)
        if AS == None:
            return []
        return sorted(self.Occurences_rec(AS))
        
    def Occurences_rec(self, AS):
        if AS.n_children() == 0:
            return [AS.index]
        index_list = []
        for word in AS.children:
            list = self.Occurences_rec(AS.children[word])
            for element in list:
                index_list.append(element)
            
        return index_list


    def NOccurences(self, P):
        AS = self._search_interval(P)
        if AS == None:
            return 0
        return AS.n_leaves


    def PrintVS_AS(self, SA=None, LCP=None, r=None):
        if r==None:
            r = self.AS
        if SA==None:
            SA = self.SA
        if LCP==None:
            LCP = self.LCP
        self.PrintSA(SA)
        self.PrintLCP(LCP)
        self.AS.print_AS(r, self.T)

    
    def PrintAS_VS(self, r=None, SA=None, LCP=None):
        if r==None:
            r = self.AS
        if SA==None:
            SA = self.SA
        if LCP==None:
            LCP = self.LCP
        self.SA, self.LCP = self.AS_VS()
        self.AS.print_AS(r, self.T)
        self.PrintSA(SA)
        self.PrintLCP(LCP)
    
    
    def PrintSA(self, SA):
        print("VS:  ", end="")
        for i in range(len(self.S)):
            print(SA[i], end=" ")
        print()


    def PrintLCP(self, LCP):
        print("LCP:", end=" ")
        for i in range(1, len(LCP)):
            print(LCP[i], end=" ")
        print()


    def AS_VS(self, r=None):
        # Monta os vetores S e LCP a partir da árvore de sufixos
        global S, LCP
        if r==None:
            r = self.AS
        AS_VS_rec(r)
        S_local, LCP_local = S, LCP
        S = []
        LCP = [0]
        return S_local, LCP_local
    
S = []
LCP = [0]    
def AS_VS_rec(AS):
    global S, LCP
    if AS.n_children()==0:
        S.append(AS.index)
        return
    else:
        for word in AS.children:
            AS_VS_rec(AS.children[word])
            LCP.append(AS.k)
        LCP.pop()