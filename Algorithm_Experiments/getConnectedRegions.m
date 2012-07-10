function R = getConnectedRegions(BW)
    L = bwlabeln(BW);
    S = regionprops(L,  'BoundingBox');
    R = zeros(length(S), 4);
    [r, c] = size(BW);
    x1 = 1; x2 = 1; y1 = 1; y2 = 1;
    for i = 1 : length(S)
        x1 = S(i).BoundingBox(1);
        y1 = S(i).BoundingBox(2);
        x2 = x1 + S(i).BoundingBox(3);
        y2 = y1 + S(i).BoundingBox(4);
        R(i, :) = [max(1,uint32(x1)), min(c,uint32(x2)), max(uint32(y1),1), min(uint32(y2), r)];
    end
end