function R = edgeDensityFilter(I, d, th)
    [r, c] = size(I);
    template = ones(1, d);
    for i = 1 : r
        cnt = sum(I(i, :));
        if(cnt < 10)
            for j = 1 : c
                I(i, j) = 0;
            end
        end  
        density = conv(double(I(i, :)), template, 'same');
        for j = 1 : length(density)
            if(density < th)
                I(i,j) = 0;
            end
        end
    end
%     for i = 1 : c
%         cnt = sum(I(:,i));
%         if(cnt < 10)
%             for j = 1 : r
%                 I(j, i) = 0;
%             end
%         end
%     end
    R = I;
end