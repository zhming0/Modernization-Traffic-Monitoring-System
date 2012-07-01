function C = morphologic_process(I, diskSize)
    E = edge(I, 'roberts');
    C = imclose(E, strel('disk', diskSize));
    C = imopen(C, strel('disk', diskSize));
end
