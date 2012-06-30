function R = find_plate_area(I, h, Cd)
    V = horizontal_projection(I);
    Vdiff = diff_h(V, h);
    Vdiff_len = length(Vdiff);
    Vdiff_len_half_toInt = int(Vdiff_len/2);
    Vdiff_min = min(Vdiff) * Cd;
    Vdiff_max = max(Vdiff) * Cd;
    Vdiff_left = Vdiff(1:Vdiff_len_half_toInt);
    Vdiff_right = Vdiff(Vdiff_len_half_toInt, end);
    
    left = max(int(Vdiff_left <= Vdiff_min) .* Vdiff_left);
    right = min(int(Vdiff_right >= Vdiff_max) .* Vdiff_right);
    R = I(:, left:right);
end