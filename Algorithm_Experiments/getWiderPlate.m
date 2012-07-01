function [ result ] = getWiderPlate( src, band )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    [r, c] = size(band);
    cnt = 1;
    %src = edge(src, 'sobel', [],'vertical');
    for i = 1 : r
        data = src(band(i, 1) : band(i, 3), :);
        %figure; imshow(data);
        %[size(src) size(data)]
        proj = horizontal_projection(data);
        %size(proj)
        %(band(i, 3) - band(i, 1)) * 2 - 1
        proj = rank_filter(proj, (band(i, 3) - band(i, 1)) * 2 - 1);
        %size(proj)
        %figure; plot(proj);
        temp = getPeakBound(proj, 0.56);
        [tr, tc] = size(temp);
        
        for j = 1 : tr
            %left = temp(j, 1) - (band(i, 3) - band(i, 1));
            left = temp(j, 1);
            %Because there is a dot...
            if left <= 1
                left = 1;
            end
            
            if (temp(j, 3) - left <= band(i, 3) - band(i, 1) * 2)
                continue;
            end
            if (temp(j, 3) > 410)
                %temp
            end
            result(cnt, :) = [left, temp(j, 3), band(i, 1), band(i, 3)];
            cnt = cnt + 1;
        end
        %break;
    end
end

