function R = rank_filter(V, n)
    template = ones(1,n) / n;
    R = conv(V, template);
    [~, c] = size(R);
    R = R(1, int32(n/2): c - int32(n/2));
end