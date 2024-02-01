from matplotlib import pyplot as plt


def union_skyline(A, B):
    # estruturando os skylines de modo mais organizado
    Ax = [A[i] for i in range(0, len(A), 2)]
    Ay = [A[i] for i in range(1, len(A), 2)]
    Ay.append(0) #ter o último y=0 facilita nas contas
    Bx = [B[i] for i in range(0, len(B), 2)]
    By = [B[i] for i in range(1, len(B), 2)]
    By.append(0) #ter o último y=0 facilita nas contas

    # inicializa, com os primeiros elementos
    aux_Ax = [0]
    aux_Ay = [Ay[0]]
    aux_Bx = [0]
    aux_By = [By[0]]

    i=1
    j=1
    # copia A e B com o intervalo inteiro, com repetições onde tem buracos
    while i < len(Ax) and j < len(Bx):
        if Ax[i] < Bx[j]:
            aux_Ax.append(Ax[i])
            aux_Ay.append(Ay[i])
            aux_Bx.append(Ax[i])
            aux_By.append(By[j-1])
            i += 1
        elif Ax[i] > Bx[j]:
            aux_Bx.append(Bx[j])
            aux_By.append(By[j])
            aux_Ax.append(Bx[j])
            aux_Ay.append(Ay[i-1])
            j += 1
        else:
            aux_Ax.append(Ax[i])
            aux_Ay.append(Ay[i])
            aux_Bx.append(Bx[j])
            aux_By.append(By[j])
            i += 1
            j += 1
    # copia o restante de A
    while i < len(Ax):
        aux_Ax.append(Ax[i])
        aux_Ay.append(Ay[i])
        aux_Bx.append(Ax[i])
        aux_By.append(By[j-1])
        i += 1
    # copia o restante de B
    while j < len(Bx):
        aux_Bx.append(Bx[j])
        aux_By.append(By[j])
        aux_Ax.append(Bx[j])
        aux_Ay.append(Ay[i-1])
        j += 1

    # lista C com os maiores y
    i=0
    Cx = []
    Cy = []
    while i < len(aux_Ax):
        if aux_Ay[i] > aux_By[i]:
            Cx.append(aux_Ax[i])
            Cy.append(aux_Ay[i])
        else:
            Cx.append(aux_Bx[i])
            Cy.append(aux_By[i])
        i += 1

    # remove repetições de C
    D = []
    for i in range(1, len(Cx)):
        if Cx[i] != Cx[i-1]:
            D.append(Cx[i-1])
            D.append(Cy[i-1])
    if Cx[i] != Cx[i-1]: D.append(Cx[i])

    return D


def plotSkyline(S):
    skylineX = []
    skylineY = []
    for x in range(0, len(S)-2, 2):
        skylineX.append(S[x])
        skylineX.append(S[x+2])
    skylineX.append(S[-1])
    for y in range(1, len(S), 2):
        skylineY.append(S[y])
        skylineY.append(S[y])
    skylineY.append(0)
    plt.plot(skylineX, skylineY)


plt.figure()
plt.title("Skyline")

S1 = (0, 0, 4, 7, 7, 4, 11, 7, 15, 1, 17)
print("S1: ", S1)

S2 = (0, 0, 2, 6, 12, 1, 20)
print("S2: ", S2)

plotSkyline(S1)
plotSkyline(S2)

# plt.show()

S3 = union_skyline(S1, S2)
print("S3: ", S3)
plotSkyline(S3)

plt.show()