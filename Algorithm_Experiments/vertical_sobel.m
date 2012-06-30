function E = vertical_sobel(I)
    E = edge(I, 'sobel',0.1, 'vertical');
end