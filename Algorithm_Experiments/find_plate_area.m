function R = find_plate_area(src, widerplate, h, Cd)

    x1 = widerplate(1, 1);
    x2 = widerplate(1, 2);
    y1 = widerplate(1, 3);
    y2 = widerplate(1, 4);
    I = src(y1:y2, x1:x2);
    
    V = horizontal_projection(I);
    Vdiff = diff_h(V, h);
    Vdiff_len = length(Vdiff);
    Vdiff_len_half_toInt = int32(Vdiff_len/2);
    Vdiff_min = min(Vdiff) * Cd;
    Vdiff_max = max(Vdiff) * Cd;
    Vdiff_left = Vdiff(1:Vdiff_len_half_toInt);
    Vdiff_right = Vdiff(Vdiff_len_half_toInt, end);
    
    left = max(int32(Vdiff_left <= Vdiff_min) .* Vdiff_left);
    right = min(int32(Vdiff_right >= Vdiff_max) .* Vdiff_right);
    %R = I(:, left:right);
    R = [left, right, y1, y2];
end