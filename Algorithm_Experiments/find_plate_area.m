function R = find_plate_area(src, widerplate, h, Cd)

    x1 = widerplate(1, 1);
    x2 = widerplate(1, 2);
    y1 = widerplate(1, 3);
    y2 = widerplate(1, 4);
    I = src(y1:y2, x1:x2);
    %figure; imshow(I);
    V = horizontal_intensity_projection(I);
%     V = rank_filter(double(V), 9);
    %figure; plot(V);
    Vdiff = diff_h(V, h);
    %Vdiff
    %size(Vdiff)
%     figure; plot(Vdiff);
    Vdiff_len = length(Vdiff);
    Vdiff_len_half_toInt = int32(Vdiff_len/2);
    Vdiff_min = min(Vdiff) * Cd;
    Vdiff_max = max(Vdiff) * Cd;
    Vdiff_left = Vdiff(1:Vdiff_len_half_toInt);
    Vdiff_right = Vdiff(Vdiff_len_half_toInt:end);
    
     MAX = -100000000; MIN = 100000000;
     left = 1; right = 1;
    for i = 1 : length(Vdiff_left)
        if (Vdiff_left(i) <= Vdiff_min && Vdiff_left(i) >=  MAX)
            MAX = Vdiff_left(i);  
            left = i;
        end
    end
    for i = 1 : length(Vdiff_right)
        if (Vdiff_right(i) >= Vdiff_max && Vdiff_right(i) <=  MIN)
            MIN = Vdiff_right(i);  
            right = i;
        end
    end
    
%     [~,right] = max(((Vdiff_right <= Vdiff_min)~=0) .* Vdiff_right);
%     plot(((Vdiff_right <= Vdiff_min)~=0) .* Vdiff_right);
%     [~,left] = min(((Vdiff_left >= Vdiff_max)~=0) .* Vdiff_left);
    %R = I(:, left:right);
    %figure; plot(Vdiff_right);
    R = [x1 + left, x1 + right + Vdiff_len_half_toInt, y1, y2];
    %[x1 + left, x1 + right + Vdiff_len_half_toInt]
    [left, right]
end