function [ result ] = getPeakBound( vector, step )
%step phase 1 = 0.55, phase 2 = 0.42
    [~, c] = size(vector);
    left = -1;
    right = -1;
    flag = 0;
    idx = 1;
    result = [];
    while left ~= -1 && right ~= -1 && left ~= right && idx <= 1|| flag == 0
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
       if (right ~= -1 && left ~= -1)
           result(idx, :) = [left, maxindex, right];
           idx = idx + 1;
           for i = left : right
                vector(1, i) = 0;
           end
       end
    end
end

