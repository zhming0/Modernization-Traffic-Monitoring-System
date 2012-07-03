function [ result ] = entropy_recognize( target, isHan )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    if nargin < 2
        isHan = 0;
    end
    [template_list, cnt] = getTemplateList();
    target = (target ~= 1);
    for i = 1 : cnt
        if (isHan == 1 && length(template_list(i).character) < 2)
            list(i, :) = 1000000000;
            continue;
        elseif isHan == 0 && length(template_list(i).character) > 1
            list(i, :) = 1000000000;
            continue;
        end
        temp = or(target, template_list(i).data);
        list(i, :) = entropy(temp);
    end
    [~, index] = min(list);
    result = template_list(index).character;
end

