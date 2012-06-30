function [] = test_main( path)
    I = imread(path);
    I = rgb2gray(I);
    figure; imshow(I);
    E = edge(I, 'sobel',0.1, 'vertical');
    E = imclose(E, strel('disk',2));
    figure; imshow(E);
    proj = vertical_projection(E);
    proj = rank_filter(proj);
    figure; plot(proj);
    bands = getPeakBound(proj, 0.55);
    getWiderPlate(I, bands)
end