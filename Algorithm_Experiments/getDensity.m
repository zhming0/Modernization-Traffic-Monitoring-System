function R = getDensity(I)
     R = conv2(I, [1,1,1;1,1,1;1,1,1]) / 9;
end