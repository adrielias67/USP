
img = input("Digite o nome da foto a ser testada: ", 's');
k = input("Digite a taxa de compressao: ");
method = input("Digite o metodo de decompressao: ");
h = input("Digite o tamanho do quadrado: ");

%funciona com imagem 100p-k X 100p-k 
compress(img, k);
disp("Imagem comprimida");
decompress(["compressed_", img], method, k, h);
disp("Imagem descomprimida");
erro = calculateError(img, ["decompressed_", img])