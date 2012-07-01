function [ result ] = heuristic_sort( src, plates )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
    [r, ~] = size(plates);
    %src = edge(src, 'sobel', [],'vertical');
    idx = 1;
    for i = 1 : r
       a1 = plates(i, 4) - plates(i, 3);
       
       x1 = plates(i, 1);
       x2 = plates(i, 2);
       y1 = plates(i, 3);
       y2 = plates(i, 4);
       
       data = src(y1 : y2, x1 : x2);
       proj = vertical_projection(data);
       a2 = 1/(max(proj));
       a3 = 1/(sum(proj));
       a4 = abs(abs((x2 - x1) / (y2 - y1)) - 3.14);
       %a4
       %result(idx, :) = 0.15 * a1 + 0.25 * a2 + 0.4 * a3 + 0.4 * a4;
       result(idx, :) = 0.1 * a1 + 0.45 * a2 + 0.25 * a3 + 0.4 * a4 + 0.5 * i;
       %result(idx, :)
       idx = idx + 1;
    end
end

