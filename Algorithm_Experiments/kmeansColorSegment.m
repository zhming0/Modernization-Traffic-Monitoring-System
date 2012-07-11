function [R, ratio] = kmeansColorSegment(I, nColors, nReplicates, limit)
    R = [];
    ratio = [];
    if(isempty(limit))
        limit = 1;
    end
    he = I;
    cform = makecform('srgb2lab');
    lab_he = applycform(he,cform);
    ab = double(lab_he(:,:,2:3));
    nrows = size(ab,1);
    ncols = size(ab,2);
    ab = reshape(ab,nrows*ncols,2);
    % repeat the clustering 3 times to avoid local minima
    [cluster_idx cluster_center] = kmeans(ab,nColors,'distance','sqEuclidean', ...
                                          'Replicates',nReplicates, 'EmptyAction', 'drop', 'OnlinePhase', 'off');
    pixel_labels = reshape(cluster_idx,nrows,ncols);
%     imshow(pixel_labels,[]), title('image labeled by cluster index');
    segmented_images = cell(1,3);
    rgb_label = repmat(pixel_labels,[1 1 3]);
    for k = 1:nColors
        color = he;
        color(rgb_label ~= k) = 0;
        segmented_images{k} = color;  
        [Is, rat] = isPlateInside(segmented_images{k}, limit);
         if (Is)
            R = segmented_images{k};
            ratio = rat;
         end
    end
end