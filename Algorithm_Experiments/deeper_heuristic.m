function [ result ] = deeper_heuristic( src, plate )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    %size(plate)
    x1 = plate(1, 1);
    x2 = plate(1, 2);
    y1 = plate(1, 3);
    y2 = plate(1, 4);
    data = src(y1 : y2, x1 : x2);
    data = data + 1;
    [r, c] = size(data);
    tmp = zeros(1, r * c);
    idx = 1;
    hostgram = zeros(1, max(max(data)));
    for i = 1 : r
        for j = 1 : c
            hostgram(1, data(i,j)) = hostgram(1, data(i,j)) + 1;
            tmp(1, idx) = data(i, j);
            idx = idx + 1;
        end
    end
    mid = median(int32(tmp));
    cnt1 = 0; cnt2 = 0;
    for i = 1 : mid
        cnt1 = cnt1 + hostgram(1, i);
    end
    l = max(max(data));
    for i = int32(mid) : int32(l)
        cnt2 = cnt2 + hostgram(1, i);
    end
    %[cnt1, cnt2]
    if abs(abs((x2 - x1) / (y2 - y1)) - 3.14) > 3
        result = 0;
    else
    if (cnt2 >= cnt1)
        result = 0;
    elseif (cnt2 < cnt1 * 0.1)
        result = 0;
    else
        result = 1;
    end 
end

