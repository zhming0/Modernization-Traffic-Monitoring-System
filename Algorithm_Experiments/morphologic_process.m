function C = morphologic_process(I)
I = histeq(I);
figure; imshow(I);
C = edge(I, 'canny');
end
