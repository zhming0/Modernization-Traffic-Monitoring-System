function mark_in_figure(I, pos, direction, marker)
    [r, c] = size(I);
    hold on;
    switch(direction)
        case 'vertical'
            plot(ones(r)* pos, 1 : r, marker);
        case 'horizontal'
            plot(1 : c,ones(c)* pos ,marker);
    end
     hold off;
end