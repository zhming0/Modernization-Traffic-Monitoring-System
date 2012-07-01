function Vdiff = diff_h(V, h)
    len_V = length(V);
    Vdiff = zeros(1,len_V - h);
    for i = 1 : len_V - h
        Vdiff(1,i) = V(1,i + h) - V(1,i);
    end
end