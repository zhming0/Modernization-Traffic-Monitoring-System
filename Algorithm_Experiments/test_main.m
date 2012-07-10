function [] = test_main(path)
    RGB = imread(path);
    I = rgb2gray(RGB);
    figure; imshow(I);
    H = fspecial('gaussian', [3,3], 0.5);
    I = imfilter(I, H);
    I = medfilt2(I, [30, 2]);
    E = edge(I, 'sobel', [],'vertical');
    figure; imshow(E);
    proj = vertical_projection(E);
    proj = rank_filter(proj, 9);
    figure; plot(proj);
    step = 0.35;
    bands = getPeakBound(proj, step);

    [r, ~] = size(bands); 
    while (r == 0)
        bands = getPeakBound(proj, step * 1.2);
        step = step * 1.2;
        [r, ~] = size(bands);
    end
    widerplate = getWiderPlate(E, bands);
    
    
    
    
    
    
    
    
    if 0
    [r, ~] = size(widerplate);
    for i = 1 : r
        widerplate(i, :) = find_plate_area(I, widerplate(i, :), int32((widerplate(i, 2) - widerplate(i, 1)))/20, 0.3);
    end
    sorted_plates = heuristic_sort(E, widerplate);
    [~, index] = min(sorted_plates);
%     sorted_plates
%      tmp = index;
%      while (deeper_heuristic(I, widerplate(index, :)) == 0 && sorted_plates(index, :) ~= 10000000)
%         sorted_plates(index, :) =10000000;
%         [~, index] = min(sorted_plates);
%         %index
%     end
%     if (sorted_plates(index, :) == 10000000)
%         index = tmp;
%     end
    mark_in_figure(I, widerplate(index, 1), 'vertical', '-b');
    mark_in_figure(I, widerplate(index, 2), 'vertical', '-r');
    mark_in_figure(I, widerplate(index, 3), 'horizontal', '-b');
    mark_in_figure(I, widerplate(index, 4), 'horizontal', '-r');
    R = I(widerplate(index, 3) : widerplate(index, 4), widerplate(index, 1): widerplate(index, 2));
    RGB = RGB(widerplate(index, 3) : widerplate(index, 4), widerplate(index, 1): widerplate(index, 2), :);
    pieces = extract_pieces_2(RGB, 1);
    
    end
    %entropy_recognize(pieces(1).image, 1)
%     stupid_recognize(pieces(1).image, 1)
%      for i = 2 : length(pieces)
%          stupid_recognize(pieces(i).image, 0)
%          %entropy_recognize(pieces(i).image, 0)
%      end
end