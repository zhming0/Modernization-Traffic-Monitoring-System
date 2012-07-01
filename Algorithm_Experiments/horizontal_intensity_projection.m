function [ V ] = horizontal_intensity_projection( I )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    [r, c] = size(I);
    I = int32(I);
    V = int32(zeros(1, c));
    for j = 1 : c
        for i = 1 : r
            V(1, j) = V(1, j) + I(i, j);
        end
    end

end

