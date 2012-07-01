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
        %int32((widerplate(i, 4) - widerplate(i, 3)))/2
        %if (widerplate(i, 4) - widerplate(i, 3) > 4)
        %widerplate(i, 4) - widerplate(i, 3)
        %widerplate(i, :) = find_plate_area(I, widerplate(i, :), int32((widerplate(i, 4) - widerplate(i, 3))), 0.5);
        %break;
    end
    
    sorted_plates = heuristic_sort(E, widerplate);
    [~, index] = max(sorted_plates);
    mark_in_figure(I, widerplate(index, 1), 'vertical', '-b');
    mark_in_figure(I, widerplate(index, 2), 'vertical', '-r');
    mark_in_figure(I, widerplate(index, 3), 'horizontal', '-b');
    mark_in_figure(I, widerplate(index, 4), 'horizontal', '-r');
end