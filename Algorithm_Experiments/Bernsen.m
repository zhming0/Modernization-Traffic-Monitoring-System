function R = Bernsen(I)
w = 1;%�����СΪ2*w+1  
T = 0;%��ֵ��С  
max = 0;  
min = 0;  
[m,n] = size(I);  
T = zeros(m - 2*w,n - 2*w);  
  
%����bersen�㷨����ÿ�����ص����ֵ  
for i = (w + 1):(m - w)  
    for j = (w + 1):(n - w)  
        max = uint8(I(i,j));  
        min = uint8(I(i,j));  
        for k = -w:w  
            for l = -w:w  
                if max < uint8(I(i + k,j + l))  
                    max = uint8(I(i + k,j + l));  
                end  
                if min > uint8(I(i + k,j + l))  
                    min = uint8(I(i + k,j + l));  
                end  
            end  
        end  
        T(i,j) = 0.5*(max + min);  
    end  
end  
for i = (w + 1):(m - w)  
    for j = (w + 1):(n - w)  
        if I(i,j) > T(i,j)  
            I(i,j) = uint8(255);  
        else  
            I(i,j) = uint8(0);  
        end  
    end  
end  
    R = logical(I);
end