function [ result ] = blur_recognize( target, isHan )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    if nargin < 2
        isHan = 0;
    end
    [template_list, cnt] = getTemplateList();
    %target = (target ~= 1);
    target = ~target;
    list = zeros(cnt, 1);
    for i = 1 : cnt
        if (isHan == 1 && length(template_list(i).character) < 2)
            list(i, :) = -1000000000;
            continue;
        elseif isHan == 0 && length(template_list(i).character) > 1
            list(i, :) = -1000000000;
            continue;
        end
        template_list(i).data = imdilate(template_list(i).data, strel('disk', 1));
        avg_t = mean(mean(template_list(i).data));
        avg_i = mean(mean(target));
        %[avg_t, avg_i]
        factor = sum(sum((target - avg_i) .* (template_list(i).data - avg_t)));
        deno = sqrt(sum(sum((target - avg_i).^2))) * sqrt(sum(sum((template_list(i).data - avg_t).^2)));
        list(i, :) = factor / deno;
    end
    [~, index] = max(list);
    result = template_list(index).character;
end

