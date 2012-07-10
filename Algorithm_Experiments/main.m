function pieces = main(filepath)
     RGB = imread(filepath);
     GRAY = rgb2gray(RGB);
    
    % Gets plate area mask.
    [ColorSegmentResult, ratio] = kmeansColorSegment(RGB, 5, 10, 1);
    if(~isempty(ColorSegmentResult))
        itCnt = 1;
        ColorSegmentResult_temp =[];
        while(ratio > 0.05)
            [ColorSegmentResult_temp, ratio] = kmeansColorSegment(ColorSegmentResult, 5 + itCnt, 10, 1);
            itCnt = itCnt + 1;
        end
        if(~isempty(ColorSegmentResult_temp))
            ColorSegmentResult = ColorSegmentResult_temp;
        end
        I = rgb2hsv(ColorSegmentResult);
        I = I(:,:,3);
        I = I~=0;
        I = edgeDensityFilter(I,10,5);
        I = imclose(I, strel('disk', 10));
        widerplate = getConnectedRegions(I);
        I = imfilter(GRAY, fspecial('gaussian', [3,3], 0.5));
        I = medfilt2(I, [10, 2]);
        E = edge(I, 'sobel', [],'vertical');
        E = edgeDensityFilter(E,10,5); 
        E = imclose(E, strel('rectangle', [5, 10]));
        
        sorted_plates = heuristic_sort(E, widerplate);
        [~, index] = min(sorted_plates);   
        I = uint8(zeros(size(RGB)));
        for i = widerplate(index, 3) : widerplate(index, 4)
            for j = widerplate(index, 1) : widerplate(index, 2)
                I(i, j, :) = RGB(i, j, :);
            end
        end
        I = rgb2hsv(I);
        I = I(:,:,3);
        I = I~=0;
        
        PlateAreaMask = I;
    else
        % Filters GRAY and Edge with Sobel to E
        I = imfilter(GRAY, fspecial('gaussian', [3,3], 0.5));
        I = medfilt2(I, [10, 2]);
        E = edge(I, 'sobel', [],'vertical');
        E = edgeDensityFilter(E,10,5); 
        E = imclose(E, strel('rectangle', [5, 10]));

        % Vertical projects E and rank filters the result to vector proj
        proj = vertical_projection(E);
        proj = rank_filter(proj, 9);

        % Gets the wide candidates in vertical axis. 
        step = 0.05;
        bands = getPeakBound(proj, step);
        [br, ~] = size(bands); 
        while (br == 0)
            step = step * 1.2;
            bands = getPeakBound(proj, step);
            [br, ~] = size(bands);
        end
        widerplate = getWiderPlate(E, bands);
        [wr, ~] = size(widerplate);
        for i = 1 : wr
            widerplate(i, :) = find_plate_area(I, widerplate(i, :), int32((widerplate(i, 2) - widerplate(i, 1)))/20, 0.3);
        end
        sorted_plates = heuristic_sort(E, widerplate);
        [~, index] = min(sorted_plates);   
        I = uint8(zeros(size(RGB)));
        for i = widerplate(index, 3) : widerplate(index, 4)
            for j = widerplate(index, 1) : widerplate(index, 2)
                I(i, j, :) = RGB(i, j, :);
            end
        end
        I = rgb2hsv(I);
        I = I(:,:,3);
        I = I~=0;
        PlateAreaMask = I;
    end
    plate = getMaskedImage(RGB, PlateAreaMask);
    if(isempty(plate))
        return;
    end
    pieces = getPieces(plate, 1);
end