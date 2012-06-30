function [ result ] = getBand( vector, step )
%step phase 1 = 0.55, phase 2 = 0.42
    [r, c] = size(vector);
    left = -1;
    right = -1;
    flag = 0;
    idx = 1;
    while left ~= -1 && right ~= -1 && left ~= right && idx <= 5|| flag == 0
        %left, right
       [maxvalue, maxindex] = max(vector);
       left = -1; right = -1;
       flag = 1;
       for i = maxindex : c
            if vector(1, i) <= maxvalue * step
                right = i;
                break;
            end
       end
       for i = fliplr(1 : maxindex)
           if vector(1, i) <= maxvalue * step
               left = i;
               break;
           end
       end
       if (right ~= -1 && right ~= -1)
           result(idx, :) = [left, maxindex, right];
           idx = idx + 1;
       end
       
       if left == -1 || right == -1
           break;
       end
       
       for i = left : right
           vector(1, i) = 0;
       end
    end
end

