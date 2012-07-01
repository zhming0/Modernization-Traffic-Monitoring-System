function [ result ] = stupid_recognize( target )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
    template = 'template/';
    list = dir(template);
    len = length(list);
    for i = 1 : len
        if (list(i).name(1) == '.')
            continue;
        end
        s = list(i).name(1:findstr(list(i).name, '.') - 1);
        node = struct('character', s, 'data', rgb2gray(imread([template , list(i).name]))); 
        %size(node.data)
    end
end

