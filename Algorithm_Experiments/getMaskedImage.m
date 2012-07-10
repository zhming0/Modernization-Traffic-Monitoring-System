function R = getMaskedImage(RGB, mask)
    R = [];
    widerplate = getConnectedRegions(mask);
    if(isempty(widerplate))
        return;
    end
    x1 = widerplate(1, 1);
    x2 = widerplate(1, 2);
    y1 = widerplate(1, 3);
    y2 = widerplate(1, 4);
    R = RGB(y1:y2, x1:x2, :);
end