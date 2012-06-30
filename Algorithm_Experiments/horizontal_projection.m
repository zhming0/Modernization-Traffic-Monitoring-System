function V = horizontal_projection(I)
    [r, c] = size(I);
    V = zeros(1, r);
    for i = 1 : c
        for j = 1 : r
            if I(i, j)~= 0
                V(1, j) = V(1, j) + 1;
            end
        end
    end
end
