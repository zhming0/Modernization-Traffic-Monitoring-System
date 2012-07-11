function [R, ratio] = isPlateInside(I, limit)
    [Color, ratio] = detect(I, limit);
    R = strcmp(Color, 'blue');
end

function [Color, ratio] = detect(I, limit)
    I = rgb2hsv(I);
    H = I(:,:,1)*360;
    S = I(:,:,2);
    V = I(:,:,3);
    ratio = [];
    ratio = length(V(V~=0))/length(V(V~=-1));
    if ratio > 0.10 && limit
        Color = 'NaN';
        return;
    end
    [r, c] = size(V);
    for i = 1 : r
        for j = 1 : c
            if H(i, j) >=345 || H(i, j) < 15
                H(i, j) = 0;
            elseif H(i, j) >= 15 && H(i, j) < 25
                H(i, j) = 1;
            elseif H(i, j) >= 25 && H(i, j) < 45
                H(i, j) = 2;
            elseif H(i, j) >= 45 && H(i, j) < 55
                H(i, j) = 3;
            elseif H(i, j) >= 55 && H(i, j) < 80
                H(i, j) = 4;
            elseif H(i, j) >= 80 && H(i, j) < 108
                H(i, j) = 5;
            elseif H(i, j) >= 108 && H(i, j) < 140
                H(i, j) = 6;
            elseif H(i, j) >= 140 && H(i, j) < 165
                H(i, j) = 7;
            elseif H(i, j) >= 165 && H(i, j) < 190
                H(i, j) = 8;
            elseif H(i, j) >= 190 && H(i, j) < 220
                H(i, j) = 9;
            elseif H(i, j) >= 220 && H(i, j) < 255
                H(i, j) = 10;
            elseif H(i, j) >= 255 && H(i, j) < 275
                H(i, j) = 11;
            elseif H(i, j) >= 275 && H(i, j) < 290
                H(i, j) = 12;
            elseif H(i, j) >= 290 && H(i, j) < 316
                H(i, j) = 13;
            elseif H(i, j) >= 316 && H(i, j) < 330
                H(i, j) = 14;
            elseif H(i, j) >= 330 && H(i, j) < 345
                H(i, j) = 15;
            end
            if S(i, j) >= 0 && S(i, j) < 0.15
                S(i, j) = 0;
            elseif S(i, j) >= 0.15 && S(i, j) < 0.4
                S(i, j) = 1;
            elseif S(i, j) >= 0.4 && S(i, j) < 0.75
                S(i, j) = 2;
            elseif S(i, j) >= 0.75 && S(i, j) <= 1
                S(i, j) = 3;
            end
            if V(i, j) >= 0 && V(i, j) < 0.15
                V(i, j) = 0;
            elseif V(i, j) >= 0.15 && V(i, j) < 0.4
                V(i, j) = 1;
            elseif V(i, j) >= 0.4 && V(i, j) < 0.75
                V(i, j) = 2;
            elseif V(i, j) >= 0.75 && V(i, j) <= 1
                V(i, j) = 3;
            end
        end
    end
%     H(V~=0)


     [~,maxofH] = max(hist(H(V~=0), 1:15));
     [~,maxofS] = max(hist(S(V~=0), 1:4));
     [~,maxofV] = max(hist(V(V~=0), 1:4));
%      maxofH
%     fprintf('H = %d;S = %d;V = %d;\n', maxofH, maxofS, maxofV);
    
    if (maxofV == 0)
        Color = 'black';
    else
        if maxofV == 3 && maxofS == 0
            Color = 'white';
        else
            if maxofH == 2
                Color = 'yello';
            else
                if maxofH == 9 || maxofH == 10
                    Color = 'blue';
                else
                    Color = 'NaN';
                end
            end
        end
    end
%     if(strcmp(Color, 'blue'))
%         figure; 
%         subplot(142);
%      hist(H(V~=0),1:15);
%      subplot(143);
%     hist(S(V~=0), 1:4);
%     subplot(144);
%     hist(V(V~=0), 1:4)
%     end
end