function compress(originalImage, k)
    img = imread(originalImage);
    p = columns(img);
    n = ceil(p / (k+1));
    compressedImage = ones(n, n, 3);

    for i = 1:p
        for j = 1:p
            if(and(rem(i,k+1)==1, rem(j,k+1)==1))
                iNew = ((i-1)/(k+1)) + 1;
                jNew = ((j-1)/(k+1)) + 1;
                compressedImage(iNew, jNew, :) = img(i, j, :);
            endif
        endfor
    endfor

    compressedImage = uint8(compressedImage);
    name = strcat("compressed_", originalImage);
    imwrite(compressedImage, name, 'Quality', 100);
endfunction