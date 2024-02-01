function decompress(compressedImg, method, k, h)
    img = imread(compressedImg);
    n = columns(img);
    p = n + ((n-1) * k);
    decompressedImage = ones(p, p, 3);



    % Bilinear %
    if(method == 1)
        M = double([1 0 0 0; 1 0 h 0; 1 h 0 0; 1 h h (h*h)]);

        for c = 1:3
            for i = 1:n-1
                for j = 1:n-1
                    f1 = img(i, j, c);
                    f2 = img(i, j+1, c);
                    f3 = img(i+1, j, c);
                    f4 = img(i+1, j+1, c);
                    f = double([f1; f2; f3; f4]);
                    
                    a = linsolve(M, f);

                    iNew = (i + (i-1)*k);
                    jNew = (j + (j-1)*k);

                    for m = iNew:(i+(i*k)+1)
                        for l = jNew:(j+(j*k)+1)
                            decompressedImage(m, l, c) = calculatePolynomialBlin(a, m, l, iNew, jNew);
                        endfor
                    endfor
                    
                endfor
            endfor
        endfor



    % Bicubica %
    else
        B = double([1 0 0 0; 1 h (h*h) (h*h*h); 0 1 0 0; 0 1 (2*h) (3*h*h)]);

        for c = 1:3
            for i = 1:n-1
                for j = 1:n-1
                    f1 = img(i, j, c);
                    f2 = img(i, j+1, c);
                    f3 = dy(img, c, i, j, h, n);
                    f4 = dy(img, c, i, j+1, h, n);

                    f5 = img(i+1, j, c);
                    f6 = img(i+1, j+1, c);
                    f7 = dy(img, c, i+1, j, h, n);
                    f8 = dy(img, c, i+1, j+1, h, n);

                    f9 = dx(img, c, i, j, h, n);
                    f10 = dx(img, c, i, j+1, h, n);
                    f11 = dxdy(img, c, i, j, h, n);
                    f12 = dxdy(img, c, i, j+1, h, n);

                    f13 = dx(img, c, i+1, j, h, n);
                    f14 = dx(img, c, i+1, j+1, h, n);
                    f15 = dxdy(img, c, i+1, j, h, n);
                    f16 = dxdy(img, c, i+1, j+1, h, n);

                    f = double([f1 f2 f3 f4; f5 f6 f7 f8; f9 f10 f11 f12; f13 f14 f15 f16]);
                    
                    a = inv(B) * f * inv(transpose(B));

                    iNew = (i + (i-1)*k);
                    jNew = (j + (j-1)*k);

                    for m = iNew:(i+(i*k)+1)
                        for l = jNew:(j+(j*k)+1)
                            decompressedImage(m, l, c) = calculatePolynomialBcubic(a, m, l, iNew, jNew);
                        endfor
                    endfor

                endfor
            endfor
        endfor
    endif



    decompressedImage = uint8(decompressedImage);
    name = strrep(compressedImg, "compressed_", "");
    name = ["decompressed_" , name];
    imwrite(decompressedImage, name, 'Quality', 100);
endfunction





function value = calculatePolynomialBlin(coefficients, m, l, iNew, jNew)
    value = coefficients(1) + coefficients(2)*(m-iNew) + coefficients(3)*(l-jNew) + coefficients(4)*(m-iNew)*(l-jNew);
endfunction



function value = calculatePolynomialBcubic(coefficients, m, l, iNew, jNew)
    value = [1 (m-iNew) ((m-iNew)^2) ((m-iNew)^3)] * coefficients * [1; (l-jNew); ((l-jNew)^2); ((l-jNew)^3)];
endfunction



function value = dx(img, c, x, y, h, n)
    % caso de exceção
    if(x == 1)
        value = ((img(2, y, c)) - img(1, y, c)) / h;

    elseif(x == n)
        value = ((img(n, y, c)) - img(n-1, y, c)) / h;

    % caso geral
    else
        value = ((img(x+1, y, c)) - img(x-1, y, c)) / (2*h);
    endif
endfunction



function value = dy(img, c, x, y, h, n)
    % caso de exceção
    if(y == 1)
        value = ((img(x, 2, c)) - img(x, 1, c)) / h;

    elseif(y == n)
        value = ((img(x, n, c)) - img(x, n-1, c)) / h;

    % caso geral
    else
        value = ((img(x, y+1, c)) - img(x, y-1, c)) / (2*h);
    endif
endfunction



function value = dxdy(img, c, x, y, h, n)
    % caso de exceção
    if(x == 1)
        value = (dy(img, c, 2, y, h, n) - dy(img, c, 1, y, h, n)) / h;

    elseif(x == n)
        value = (dy(img, c, n, y, h, n) - dy(img, c, n-1, y, h, n)) / h;

    elseif(y == 1)
        value = (dy(img, c, x+1, y, h, n) - dy(img, c, x-1, y, h, n)) / (2*h);

    elseif(y == n)
        value = (dy(img, c, x+1, y, h, n) - dy(img, c, x-1, y, h, n)) / (2*h);

    % caso geral
    else
        value = (dy(img, c, x+1, y, h, n) - dy(img, c, x-1, y, h, n)) / (2*h);
    endif
endfunction