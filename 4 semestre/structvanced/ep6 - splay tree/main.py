# Para fazer este trabalho, levei aproximadamente 9 horas.

import splay_tree as st


if __name__ == '__main__':
    splay = st.ST()

    while True:
        try:
            linha = input()
        except:
            break

        entrada = linha.split()
        operacao = int(entrada[0])
        if len(entrada) > 1:
            x = int(entrada[1])

        match operacao:
            case 1:
                splay.Insert(x)
            case 2:
                splay.Delete(x)
            case 3:
                print(int(splay.Search(x)))
            case 4:
                print(splay.Min().val)
            case 5:
                splay.Print()
            # case 6:
            #     A = st.ST()
            #     B = st.ST()
            #     A,B = splay.Split(4)
            #     B.Print()
            #     print(" --- ")
            #     A.Print()
            #     splay = st.Join(A, B)