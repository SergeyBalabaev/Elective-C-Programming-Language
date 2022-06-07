function [return_x] = birdspectr(y,Fs)
%Функция построения графика разложения записи пения в спектр
% Возвращает расположение пикового значения спектра 
x=0:1/Fs:length(y)/Fs-1/Fs;
ynew = y;
m = length(y);    % original sample length
n = pow2(nextpow2(m));  % transform length
y = fft(y,n);
f = (0:n-1)*(Fs/n);
power = abs(y).^2/n;    
x = f(1:floor(n/4));
y = power(1:floor(n/4));
%plot(y)
%cc = mean(y)
c = find(y == max(y));
%x(cc)
return_x = x(c);
end

