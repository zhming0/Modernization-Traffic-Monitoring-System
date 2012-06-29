function V = stat_vertical(I)
    [r, c] = size(I);
    V = zeros(1, r);
    for i = 1 : r
        for j = 1 : c
            if I(i, j)~= 0
                V(1, i) = V(1, i) + 1;
            end
        end
    end
end