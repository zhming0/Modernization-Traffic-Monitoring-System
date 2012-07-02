function [ result ] = stupid_recognize( target )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
    template = 'template/';
    list = dir(template);
    len = length(list);
    cnt = 0;
    
    for i = 1 : len
        if (list(i).name(1) == '.')
            continue;
        end
        cnt = cnt + 1;
        s = list(i).name(1:findstr(list(i).name, '.') - 1);
        template_list(cnt) = struct('character', s, 'data', rgb2gray(imread([template , list(i).name]))); 
        %template_list(cnt) = node;
        %size(template_list.cnt.data)
    end
    %target = rgb2gray(target) ~=0;
    %target = imresize(target, [238, 123]);
    target = (target ~= 1);
    list = zeros(cnt, 1);
    for i = 1 : cnt
        %size(target)
        %size(template_list(i).data)
        %temp = target - template_list(i).data;
        temp = and(target, template_list(i).data);
        temp2 = xor(target, template_list(i).data);
        %figure; imshow(temp);
        %list(i, :) = sum(sum(abs(temp)))/sum(sum(template_list(cnt).data));
        list(i, :) = sum(sum(abs(temp))) - sum(sum(abs(temp2)));
    end
    [~, index] = max(list);
    result = template_list(index).character;
end

