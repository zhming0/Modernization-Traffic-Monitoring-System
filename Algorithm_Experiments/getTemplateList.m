function [ result, cnt ] = getTemplateList()
%UNTITLED2 Summary of this function goes here
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
        template_list(cnt) = struct('character', s, 'data', rgb2gray(imread([template , list(i).name])) > 25); 
    end
    result = template_list;
end

