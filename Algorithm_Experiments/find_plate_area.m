function R = find_plate_area(src, widerplate, h, Cd)

    x1 = widerplate(1, 1);
    x2 = widerplate(1, 2);
    y1 = widerplate(1, 3);
    y2 = widerplate(1, 4);
    I = src(y1:y2, x1:x2);
    %[y1, y2, x1, x2]
    %figure; imshow(I);
    I = morphologic_process(I);
    %figure; imshow(I);figure;
    
    V = horizontal_intensity_projection(I);
    %figure; plot(V);
    Vdiff = diff_h(V, h);
    Vdiff_len = length(Vdiff);
    Vdiff_len_half_toInt = int32(Vdiff_len/2);
    %Vdiff_min = min(Vdiff) * Cd;
    %Vdiff_max = max(Vdiff) * Cd;
    
    Vdiff_left = Vdiff(1:Vdiff_len_half_toInt);
    Vdiff_right = Vdiff(Vdiff_len_half_toInt:end);
    
    [Vdiff_min, Vdiff_min_idx] = min(Vdiff_left);
    [Vdiff_max, Vdiff_max_idx] = max(Vdiff_right);
    Vdiff_min = Vdiff_min * Cd;
    Vdiff_max = Vdiff_max * Cd;
    
    %figure; plot(Vdiff);
    
    MAX = -100000000; MIN = 100000000;
    left = Vdiff_min_idx; right = Vdiff_max_idx;
    
    for i = 1 : Vdiff_min_idx
        if (Vdiff_left(i) <= Vdiff_min && Vdiff_left(i) >=  MAX)
            MAX = Vdiff_left(i);  
            left = i;
            break;
        end
    end
    for i = fliplr(Vdiff_max_idx : length(Vdiff_right))
        if (Vdiff_right(i) >= Vdiff_max && Vdiff_right(i) <=  MIN)
            MIN = Vdiff_right(i);  
            right = i;
            break;
        end
    end

    R = [x1 + left, x1 + right + Vdiff_len_half_toInt + h/2, y1, y2];
    %[x1 + left, x1 + right + Vdiff_len_half_toInt]
    %[left, right]
end