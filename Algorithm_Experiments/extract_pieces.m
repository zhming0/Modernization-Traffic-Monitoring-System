function pieces = extract_pieces(I)
    I = 255 - I;
    [r, c] = size(I);
    I = Bernsen(I);
    figure; imshow(I);
    V = horizontal_intensity_projection(I);
    Vm = max(V);
    Va = mean(V);
    Vb = 2*Va-Vm;
    Cx = 0.7;
    Cw = 0.86;
    ind = 1;
    while(1)
        [maxValue, maxIndex] = max(V);
        left = maxIndex;
        right = maxIndex;
        for i = fliplr(1 : maxIndex)
            if(V(i) <= Cx*maxValue)
                left = i;
                break;
            end
        end
        for i = maxIndex : length(V)
            if(V(i) <= Cx* maxValue)
                right = i;
                break;
            end
        end
        V(left:right) = V(left:right)*0;
        if(ind > 8 )
            break;
        end
        dividePoints(ind) = maxIndex;
        ind = ind + 1;
    end
    dividePoints = sort(dividePoints);
    len_dividePoints = length(dividePoints);
    hold on;
    for i = 1 : len_dividePoints
        mark_in_figure(I ,dividePoints(i), 'vertical', '-r');
    end
    hold off;
    Vpiece = vertical_projection(~I);
    figure; plot(Vpiece);
    Vpiece_max = max(Vpiece);
    Cf = 0.8;
    len_Vpiece = length(Vpiece);
    Vpiece_left = 1;
    Vpiece_right = r;
    for j = 1 : len_Vpiece
        if(Vpiece(j) >= Cf * Vpiece_max)
            Vpiece_left = j;
            break;
        end
    end
    for j = fliplr(1 : len_Vpiece)
        if(Vpiece(j) >= Cf * Vpiece_max)
            Vpiece_right = j;
            break;
        end
    end  
    for i = 1 : len_dividePoints - 1
        piece = I(1 : r, dividePoints(i):dividePoints(i+1));
        piece = piece(Vpiece_left:Vpiece_right, :);
        piece = bwareaopen(piece ,4);

        [pr, pc] = size(piece);
        Vpiece_left_ = 1;
        Vpiece_right_ = pc;
        flag = 0;
        for j = 1 : pc
            for k = 1 : pr
                if(piece(k, j) == 0)
                    Vpiece_left_ = j;
                    flag = 1;
                    break;
                end
            end
            if(flag == 1)
                break;
            end
        end
        flag = 0;
        for j = fliplr(1 : pc)
            for k = 1 : pr
                if(piece(k, j) == 0)
                    Vpiece_right_= j;
                    flag = 1;
                    break;
                end
            end
            if(flag == 1)
                break;
            end
        end
        piece = piece(: , Vpiece_left_:Vpiece_right_);
        piece = imresize(piece,[123, 238], 'bicubic');
        figure; imshow(piece);
        s = struct('image', piece);
        pieces(i) = s;
    end
end
