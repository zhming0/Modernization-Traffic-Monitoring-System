function [ result ] = getBand( vector, step )
%step phase 1 = 0.55, phase 2 = 0.42
    [r, c] = size(vector);
    left = -1;
    right = -1;
    flag = 0;
    idx = 1;
    while left ~= -1 && right ~= -1 || flag == 0
       [maxvalue, maxindex] = max(vector);
       flag = 1;
       for i = maxindex : c
            if vector(1, i) <= maxvalue * step
                right = i;
                break;
            end
       end
       for i = maxindex : 1
           if vector(1, i) <= maxvalue * step
               left = i;
               break;
           end
       end
       if (right ~= -1 && right ~= -1)
           result = [result; [left, maxindex, right]];
           idx = idx + 1;
       end
       for i = left : right
           vector(1, i) = 0;
       end
       left = -1; right = -1;
    end
end

