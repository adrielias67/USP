# Para fazer este trabalho, levei aproximadamente 10 horas.
import heap_cinetico as hc
import heap_max as hmax
import heap_min as hmin


if __name__ == '__main__':
    n = int(input())
    nos = []
    for i in range(n):
        linha = input()
        ponto = linha.split()
        x0 = int(ponto[0])
        v = int(ponto[1])
        no = hmax.no(i+1, x0, v)
        nos.append(no)
        
    now = 0
    heap_cin = hc.KinHeap(nos, n)
    
    while True:
        try:
            linha = input()
        except:
            break

        entrada = linha.split()
        operacao = int(entrada[0])
        if len(entrada) > 1:
            i = float(entrada[1])
        if len(entrada) > 2:
            x = float(entrada[2])
        if len(entrada) > 3:
            v = float(entrada[3])

        match operacao:
            case 1:
                heap_cin.Advance(i)
            case 2:
                heap_cin.Change(int(i), x)
            case 3:
                heap_cin.Insert(int(i), x, v)
            case 4:
                print(heap_cin.Max().id)
            case 5:
                heap_cin.DeleteMax()
            case 6:
                heap_cin.Delete(int(i))
            case 7:
                heap_cin.Print()