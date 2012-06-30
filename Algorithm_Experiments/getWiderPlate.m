function [ result ] = getWiderPlate( src, band )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    [r, c] = size(band);
    cnt = 1;
    for i = 1 : r
        data = src(band(i, 1) : band(i, 3), :);
        proj = horizontal_projection(data);
        proj = rank_filter(proj);
        temp = getPeakBound(proj, 0.86);
        [tr, tc] = size(temp);
        for j = 1 : tr
            result(cnt, :) = [temp(j, 1), temp(j, 3), band(i, 1), band(i, 3)];
            cnt = cnt + 1;
        end
    end
end

