function pieces = getPieces(RGB, showResult)
    
    I = rgb2gray(RGB);
    I = imresize(I, [40, 160]);
    I = uint8(I * 0.3922);
    sortVector = sort(I(I~=-1));
    threshold = sortVector(int32(length(sortVector)*0.70));
    I = max(I,  uint8(double(I > threshold) * 255));
    S_max = max(vertical_intensity_projection(I));
    S_alpha = 0;
    for i =  [1:10, fliplr(-10:-1)]
        S_this = max(vertical_intensity_projection(imrotate(I, i, 'nearest')));
        if(S_this > S_max)
            S_max = S_this;
            S_alpha = i;
        end
    end
    I = imrotate(I, S_alpha, 'nearest');
    V = double(vertical_intensity_projection(I));
    V = rank_filter(double(V), 5);
    
    threshold = mean(V) -0.5 * std(V);
    V_threshold = (V>threshold);
    S_start = 1; S_length = 0;
    for i = 1 : length(V_threshold)   
        for j = i : length(V_threshold)
            if(V_threshold(j) ~= 1)
                if(j - i > S_length)
                    S_start = i;
                    S_length = j - i;
                end
                break;
            end
        end
    end
    S_end = S_start + S_length - 1;
    S = S_start : S_end;
    I = I(S,:);
    
    [Ir, Ic] = size(I);
    CLOSE = im2bw(imclose(I, strel('line', 20, 90)), 0.8);
    V = (horizontal_intensity_projection(CLOSE))~=0;
    idx = 1;
    i = 1;
    CharColumns = [];
    while(i < length(V))
        for j = i : length(V)
            if(V(j) ~= 1)
                start = i;
                len = j - i;
                    if(len ~= 0)
                        CharColumns(idx, :) = [start, len];
                        idx = idx + 1;
                    end
                    i = j+1;
                break;
            end
        end
        if(i~=j+1)
            i = length(V);
        end
    end
    if(isempty(CharColumns))
        pieces = [];
        return;
    end
    lenCC = size(CharColumns, 1);
    CharColumnsBool = ones(lenCC, 1);
    cntRemains = lenCC;
    if(lenCC ~= 0)
        start = CharColumns(1, 1);
        len = CharColumns(1, 2);
        if(len <= 5)
            CharColumnsBool(1, 1) = 0;
            cntRemains = cntRemains - 1;
            for i = start : start + len - 1
                for j = 1 : Ir
                    I(j, i) = 0;
                end
            end
        end
        if(len >= 20)
            for i = 1 : len - 19
                for j = 1 : Ir
                    I(j, i) = 0;
                end
            end
            CharColumns(1, 1) = len - 18;
        end
    end
    PossibleDotPos = -1;
    if(CharColumnsBool(1, 1))
        if(3 < lenCC)
            PossibleDotPos = 3;
        end
    else
        if(4 < lenCC)
            PossibleDotPos = 4;
        end
    end
    if(PossibleDotPos ~= -1)
        start = CharColumns(PossibleDotPos, 1);
        len = CharColumns(PossibleDotPos, 2);
        if(len <= 5)
            CharColumnsBool(PossibleDotPos, 1) = 0;
            cntRemains = cntRemains - 1;
            for i = start : start + len - 1
                for j = 1 : Ir
                    I(j, i) = 0;
                end
            end
        end
    end
    
    if(cntRemains > 7)
        start = CharColumns(lenCC, 1);
        len = CharColumns(lenCC, 2);
        if(len < 5)
             CharColumnsBool(lenCC, 1) = 0;
             cntRemains = cntRemains - 1;
            for i = start : start + len - 1
                for j = 1 : Ir
                    I(j, i) = 0;
                end
            end
        end
    end
    I = im2bw(I, 0.8);
    idx = 1;
    for i = 1 : length(CharColumnsBool)
        if(CharColumnsBool(i, 1) == 1)
            start = max(CharColumns(i, 1), 1);
            term = min(start + CharColumns(i, 2) - 1, Ic);
            piece = I(:, start : term);
            if(sum(vertical_projection(piece)) / Ir < 0.5)
                continue;
            end
            s = struct('image', piece);
            pieces(idx) = s;
            idx = idx + 1;
        end
    end 
%     figure;
%     for i = 1 :length(pieces)
%         subplot(1, length(pieces), i);
%         imshow(pieces(i).image);
%     end
end