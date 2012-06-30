function R = rank_filter(V)
    template = ones(1,9) / 9;
    R = conv(V, template);
end