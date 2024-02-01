#------------------------------------------------------------------------------
# # MAT0122 ÁLGEBRA LINEAR I
# Aluno: Adriano Elias Andrade
# Numero USP: 13671682
# Tarefa: EP 7.8
# Data: 18/12/2022
# 
# DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA.  TODAS AS 
# PARTES DO PROGRAMA, EXCETO AS QUE SÃO BASEADAS EM MATERIAL FORNECIDO  
# PELO PROFESSOR OU COPIADAS DO LIVRO OU DO MATERIAL DIDÁTICO DE MAT0122, 
# FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS 
# AS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUÍ NEM FACILITEI A DISTRIBUIÇÃO
# DE CÓPIAS DESTA PROGRAMA.
#------------------------------------------------------------------------------


import sys
import GF2
from GF2 import one
from vec import Vec
from factoring_support import intsqrt, dumb_factor, primes, prod, gcd



def int2GF2(x):
    if x%2 == 1:
        return one
    return 0



def transformation_rows(rowlist_input, col_label_list = None):
    """Given a matrix A represented by a list of rows
        optionally given the unit field element (1 by default),
        and optionally given a list of the domain elements of the rows,
        return a matrix M represented by a list of rows such that
        M A is in echelon form
    """
    rowlist = list(rowlist_input)
    if col_label_list == None: col_label_list = sorted(rowlist[0].D, key=repr)
    m = len(rowlist)
    row_labels = set(range(m))
    M_rowlist = [Vec(row_labels, {i:one}) for i in range(m)]
    new_M_rowlist = []
    rows_left = set(range(m))
    for c in col_label_list:
        rows_with_nonzero = [r for r in rows_left if rowlist[r][c] != 0]
        if rows_with_nonzero != []:
            pivot = rows_with_nonzero[0]
            rows_left.remove(pivot)
            new_M_rowlist.append(M_rowlist[pivot])
            for r in rows_with_nonzero[1:]:
                multiplier = rowlist[r][c]/rowlist[pivot][c]
                rowlist[r] -= multiplier*rowlist[pivot]
                M_rowlist[r] -= multiplier*M_rowlist[pivot]
    for r in rows_left: new_M_rowlist.append(M_rowlist[r])
    z = len([r for r in rows_left if rowlist[r][c] == 0])
    return new_M_rowlist, z



def make_Vec(primeset, factors):
    return Vec(primeset, {x: int2GF2(y) for (x, y) in factors})



def find_candidates(N, primeset):
    roots = []
    rowlist = []
    a = intsqrt(N) + 2
    while len(rowlist) < len(primeset)+1:
        factor_list = dumb_factor(a * a - N, primeset)
        if len(factor_list) != 0:
            roots.append(a)
            rowlist.append(make_Vec(primeset, factor_list))
        a += 1
    return roots, rowlist



def find_a_and_b(v, roots, N):
    alist = [roots[i] for i in range(len(roots)) if v[i] != 0]
    a = prod(alist)
    alist_nonzero = [x * x - N for x in alist]
    c = prod(alist_nonzero)
    b = intsqrt(c)
    assert(b*b == c)
    return (a,b)





############### MAIN ###############

N = int(sys.argv[1])

if len(sys.argv) == 2:
    U = 10000
else:
    U = int(sys.argv[2])

primelist = primes(U)

verborragico = 0
if len(sys.argv) == 4:
    verborragico = 1


roots, rowlist = find_candidates(N, primelist)
M, z = transformation_rows(rowlist, sorted(primelist, reverse=True))

k = 0
for i in reversed(range(len(M)-z, len(M))):
    v = M[i]
    (a,b) = find_a_and_b(v, roots, N)
    if verborragico:
        print("{} : a = {} / b = {}".format(k, a, b))
        k += 1
    factor = gcd(a-b, N)
    if factor != 1 and factor != N:
        print("factor =", factor)
        exit (0)

print("Failed")
exit (0)

####################################