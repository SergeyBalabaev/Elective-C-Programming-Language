function [ fOut,fs ] = filter_song(f,fs,begin1,end1)
%Фильтр для песни птицы
N = size(f,1); 
%df = fs / N;
%w = (-(N/2):(N/2)-1)*df;
%y = fft(f(:,1), N) / N; 
%y2 = fftshift(y);
n = 7;
if (begin1<0)
    begin1 = 600;
end
beginFreq = begin1 / (fs/2);

endFreq = end1 / (fs/2);
[b,a] = butter(n, [beginFreq, endFreq], 'bandpass');
fOut = filter(b, a, f);
[b,a] = butter(n, 1200/(fs/2), 'high');
fOut = filter(b, a, fOut);
[b,a] = butter(n, 7000/(fs/2), 'low');
fOut = filter(b, a, fOut);


end

