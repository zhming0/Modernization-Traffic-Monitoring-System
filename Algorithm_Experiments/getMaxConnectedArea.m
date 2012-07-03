function [ result ] = getMaxConnectedArea( image, conn )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
    L = bwlabeln(image, conn);
    S = regionprops(L, 'Area');
    max = -1000000;
    %idx = 1;
    %length(S)
    for i = 1 : length(S)
        S(i).Area
        if (S(i).Area > max)
            max = S(i).Area;
            %idx = i;
        end
    end
    %'--------'
    %idx
    result = ismember(L, find([S.Area]) == max);
end

