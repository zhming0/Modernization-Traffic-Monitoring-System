function Vdiff = diff_h(V, h)
    len_V = length(V);
    Vdiff = zeros(len_V - h);
    for i = 1 : len_V - h
        Vdiff = V(i + h) - V(i);
    end
end