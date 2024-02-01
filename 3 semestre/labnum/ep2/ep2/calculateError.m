function err = calculateError(originalImg, decompressedImg)
    imgO = imread(originalImg);
    imgD = imread(decompressedImg);

    imgO = double(imgO);
    imgD = double(imgD);


    origR = imgO(:, :, 1);
    decR = imgD(:, :, 1);
    origG = imgO(:, :, 2);
    decG = imgD(:, :, 2);
    origB = imgO(:, :, 3);
    decB = imgD(:, :, 3);

    errR = (norm(origR - decR)) / (norm(origR));
    errG = (norm(origG - decG)) / (norm(origG));
    errB = (norm(origB - decB)) / (norm(origB));

    err = (errR + errG + errB) / 3;
endfunction