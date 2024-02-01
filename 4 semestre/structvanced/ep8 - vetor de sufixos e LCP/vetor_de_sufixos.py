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



class VS:
    T = []
    S = []
    SA = {}
    LCP = []
    LLCP = []
    RLCP = []


    def LRLCP(self, LCP, i, j, side):
        if i == j-1:
            value = LCP[j]
        else:
            m = (i+j)//2
            self.LRLCP(LCP, i, m, "L")
            self.LRLCP(LCP, m, j, "R")
            value = min(self.LLCP[m], self.RLCP[m])
        if side == "L":
            self.LLCP[j] = value
        if side == "R":
            self.RLCP[i] = value


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

        self.LLCP = [0]*len(self.LCP)
        self.RLCP = [0]*len(self.LCP)
        self.LRLCP(self.LCP, 0, len(self.LCP)-1, "L")


    def _search_interval(self, P, side):
        s = self.SA[len(self.T)-1]
        r = 0
        while r < len(P) and s+r<len(self.T) and P[r]==self.T[s+r]:
            r += 1
        if side=="R" and (r == len(P) or P[r] > self.T[s+r]):
            return len(self.T)
        if side=="L":
            if r==len(P):
                return len(self.S)-2
            if P[r] > self.T[s+r]:
                return len(self.S)-1

        L = 0
        l = 0
        R = len(self.T) -1
        while L < R-1:
            m = (L+R)//2
            if l==r:
                stopped = False
                for i in range(l, len(P)):
                    if P[i] < self.S[m][i]:
                        R = m
                        r = i
                        stopped = True
                        break
                    elif P[i] > self.S[m][i]:
                        L = m
                        l = i
                        stopped = True
                        break
                if not stopped:
                    if side=="R":
                        L = m
                        l = len(P)
                    if side=="L":
                        R = m
                        r = len(P)


            elif l>r:
                if l < self.LLCP[m]:
                    L = m
                elif l > self.LLCP[m]:
                    R = m
                    r = self.LLCP[m]
                else:
                    stopped = False
                    for i in range(l, len(P)):
                        if P[i] < self.S[m][i]:
                            R = m
                            r = i
                            stopped = True
                            break
                        elif P[i] > self.S[m][i]:
                            L = m
                            l = i
                            stopped = True
                            break
                    if not stopped:
                        if side=="R":
                            L = m
                            l = len(P)
                        if side=="L":
                            R = m
                            r = len(P)
            
            else:
                if r < self.RLCP[m]:
                    R = m
                elif r > self.RLCP[m]:
                    L = m
                    l = self.RLCP[m]
                else:
                    stopped = False
                    for i in range(r, len(P)):
                        if P[i] < self.S[m][i]:
                            R = m
                            r = i
                            stopped = True
                            break
                        elif P[i] > self.S[m][i]:
                            L = m
                            l = i
                            stopped = True
                            break
                    if not stopped:
                        if side=="R":
                            L = m
                            l = len(P)
                        if side=="L":
                            R = m
                            r = len(P)

        if side=="R": return R
        if side=="L": return L
    

    def Search(self, P):
        R = self._search_interval(P, "R")
        L = self._search_interval(P, "L")
        if L==len(self.S):
            return False
        if L==R-1:
            return False
        return True
                
    
    def Occurences(self, P):
        R = self._search_interval(P, "R")
        L = self._search_interval(P, "L")
        O = []
        for i in range(L+1, R):
            O.append(i)
        for i in range(len(O)):
            O[i] = self.SA[O[i]]
        return sorted(O)
    

    def NOccurences(self, P):
        R = self._search_interval(P, "R")
        L = self._search_interval(P, "L")
        if L==R:
            return 0
        return R-L-1


    def Print(self):
        self.PrintS()
        self.PrintSA()
        self.PrintLCP()

    
    def PrintSA(self):
        print("VS:  ", end="")
        for i in range(len(self.S)):
            print(self.SA[i], end=" ")
        print()


    def PrintS(self):
        for i in range(len(self.S)):
            print(i, self.S[i])
        print()


    def PrintLCP(self):
        print("LCP:", end=" ")
        for i in range(1, len(self.LCP)):
            print(self.LCP[i], end=" ")
        print()


    def PrintLLCP(self):
        print(self.LLCP)
    

    def PrintRLCP(self):
        print(self.RLCP)