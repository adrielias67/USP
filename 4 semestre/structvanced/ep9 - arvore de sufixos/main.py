# Para fazer este trabalho, levei aproximadamente 9 horas.


import arvore_de_sufixos as As


if __name__ == '__main__':

    while True:
        try:
            linha = input()
        except:
            break
    
        entrada = linha.split()
        operacao = int(entrada[0])
        if len(entrada) > 1:
            x = entrada[1]
        if len(entrada) > 2:
            x += " "
            for i in range(2, len(entrada)):
                x += entrada[i] + " "
            x = x[:len(x)-1]
    
        match operacao:
            case 1:
                A = As.AS(x)
                A.VS_AS()

            case 2:
                text = ""
                with open(x, "r") as file:
                    for line in file:
                        text += line.strip() + " "
                A = As.AS(text)
                A.VS_AS()

            case 3:
                print(A.Search(x))

            case 4:
                occ = A.Occurences(x)
                for i in range(len(occ)):
                    print(occ[i], end=" ")
                print()

            case 5:
                print(A.NOccurences(x))

            case 6:
                A.PrintVS_AS()
                
            case 7:
                A.PrintAS_VS()