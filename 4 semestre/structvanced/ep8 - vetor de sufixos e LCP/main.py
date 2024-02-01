# Para fazer este trabalho, levei aproximadamente 7 horas.


import vetor_de_sufixos as vs


if __name__ == '__main__':
    V = None

    while True:
        try:
            linha = input()
        except:
            break
    
        entrada = linha.split()
        operacao = int(entrada[0])
        if len(entrada) > 1:
            x = entrada[1]
    
        match operacao:
            case 1:
                print(x)
                V = vs.VS(x)

            case 2:
                print(x)
                text = ""
                with open(x, "r") as file:
                    for line in file:
                        text += line.strip() + " "
                V = vs.VS(text)

            case 3:
                print(V.Search(x))

            case 4:
                occ = V.Occurences(x)
                for i in range(len(occ)):
                    print(occ[i], end=" ")
                print()

            case 5:
                print(V.NOccurences(x))

            case 6:
                 V.Print()