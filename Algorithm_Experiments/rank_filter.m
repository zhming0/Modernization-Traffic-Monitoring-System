function R = rank_filter(V, n)
    template = ones(1,n) / n;
    R = conv(V, template);
    [r, c] = size(R);
    R = R(1, n/2: c - n/2);
end