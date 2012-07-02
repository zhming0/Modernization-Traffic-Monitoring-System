function [] = test_main( path)
    I = imread(path);
    I = rgb2gray(I);
    %figure; imshow(I);
    E = edge(I, 'sobel', [],'vertical');
    %E = imclose(E, strel('disk',2));
    %figure; imshow(E);
    proj = vertical_projection(E);
    proj = rank_filter(proj, 9);
    %figure; plot(proj);
    bands = getPeakBound(proj, 0.35);
    
    widerplate = getWiderPlate(E, bands);
    [r, ~] = size(widerplate);
    figure; imshow(I);
    for i = 1 : r
        widerplate(i, :) = find_plate_area(I, widerplate(i, :), int32((widerplate(i, 2) - widerplate(i, 1)))/15, 0.5);
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
    pieces = extract_pieces(R);
    
%      for i = 1 : length(pieces)
%          result(i) = stupid_recognize(pieces(i).image);
%      end
%      result
    stupid_recognize(pieces(1).image, 1)
end