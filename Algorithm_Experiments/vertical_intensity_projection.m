function [ V ] = vertical_intensity_projection( I )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    [r, c] = size(I);
    I = int32(I);
    V = int32(zeros(1, r));
    for j = 1 : c
        for i = 1 : r
            V(1, i) = V(1, i) + I(i, j);
        end
    end

end

