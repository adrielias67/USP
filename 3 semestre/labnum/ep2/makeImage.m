function makeImage(size)
    img = ones(size, size, 3);

    % red
    for i = 1:size
        for j = 1:size
            img(i, j, 1) = size+i-j;
        endfor
    endfor

    % green
    for i = 1:size
        for j = 1:size
            img(i, j, 2) = size-i+j;
        endfor
    endfor

    % blue
    for i = 1:size
        for j = 1:size
            img(i, j, 3) = i*1.5;
        endfor
    endfor

    img = uint8(img);
    imwrite(img, "function.png", 'Quality', 100);
endfunction