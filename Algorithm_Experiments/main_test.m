% main_test serves as the entry of the main function, you should specify 
%           this file as the main file when deploying. 
%             As a protocol, the function reads stdin a filename and 
%           savepath, sequantially, filename should be the image ready to 
%           be processed, savepath should be a valid, i.e. already exists
%           and visitable, directory, to which this function will save
%           the output.
%             The function responds to stdout by writing lines of symbols:
%                 [error]\n  when an error occurs;
%                 [num]<number of output files>\n returns the number of
%                 output files, say, in the correct cases, the number
%                 should be 7 and there should be an output of 
%                                    [num]7\n
%                 In other cases, the output number may not be 7, you
%                 should deal with such cases correctly.
%             The output files will be saved in the savepath, named, from
%                 1.png, 2.png, ..., <number of output files>.png .
% Tsenmu, i@tsenmu.com, 2012.
warning('off', 'all');
filename = input('');
savepath = input('');
if(~isdir(savepath))
    fprintf('[error]\n');
    return;
end
pieces = main(filename);

if(~isempty(pieces))
   for i = 1 : length(pieces)
       imwrite(pieces(i).image, strcat([savepath, '\\', num2str(i), '.png']), 'png');
   end
   fprintf(strcat(['[num]', num2str(length(pieces))], '\n'));
   return;
else
    fprintf(strcat(['[num]', num2str(0)], '\n'));
    return;
end