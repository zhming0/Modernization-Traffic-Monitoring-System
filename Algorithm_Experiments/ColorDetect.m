function ResultPlates =  ColorDetect(I, plates)
 % H = {0, [345-15]; 1, [15-25]; 2, [25, 45]; 3, [45, 55]; 4, [55, 80]; 5, 
 % [80, 108]; 6, [108, 140]; 7,[140,165];8,[165,190];9,[190,220];
 % 10,[220,255];11,[255,275];12,[275,290];13,[290,316];
 % 14,[316,330];15,[330,345] } / 360.
 % S = {0,[0, 0.15];1, [0.15, 0.4];2, [0.4, 0.75];3, [0.75, 1]}
 % V = {0, [0, 0.15]; 1, [0.15, 0.4]; 2, [0.4, 0.75]; 3,[0.75, 1]}
    ResultPlates = zeros([1, 4]);
    [r, ~] = size(plates);
    idx = 1;
    for i = 1 : r
       x1 = plates(i, 1);
       x2 = plates(i, 2);
       y1 = plates(i, 3);
       y2 = plates(i, 4);
       data = I(y1 : y2, x1 : x2, :);
       Color = detect(data);
       
       if(strcmp(Color, 'blue'))
           ResultPlates(idx, :) = plates(i, :);
           idx = idx + 1;
           figure; imshow(data);
       end
    end
end

function Color = detect(I)
    I = rgb2hsv(I);
    H = I(:,:,1)*360;
    S = I(:,:,2);
    V = I(:,:,3);
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
    [~,maxofH] = max(hist(reshape(H, 1, r*c), 15));
    [~,maxofS] = max(hist(reshape(S, 1, r*c), 4));
    [~,maxofV] = max(hist(reshape(V, 1, r*c), 4));
    maxofH
    maxofS
    maxofV
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
end