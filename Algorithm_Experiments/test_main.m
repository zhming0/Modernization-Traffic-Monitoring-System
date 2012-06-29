I = imread('002.bmp');
I = rgb2gray(I);
figure; imshow(I);
E = edge(I, 'sobel',0.1, 'vertical');
E = imclose(E, strel('disk',2));
figure; imshow(E);
figure; plot(stat_vertical(E));
