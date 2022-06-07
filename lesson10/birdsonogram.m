function [X, Y, Z, ps]=birdsonogram(y,Fs)
% Функция построения сонограммы
figure()

cmap = [1 1 1;
        1 1 1;
        1 1 1;
        1 1 1;
        1 1 1;
        1 1 1;
        1 1 1;
        1 1 1;
        1 1 1;
        1 1 1;
        1 1 1;
        0 0 0;
        0 0 0;
        0 0 0];
    
subplot(2,1,1);
x=0:1/Fs:length(y)/Fs-1/Fs;
plot(x,y);
xlabel('Time')
ylabel('Amplitude')
subplot(2,1,2);
y=abs(y(:,1));    
[X, Y, Z, ps]=spectrogram(y,kaiser(256,10),220,1024,Fs,'yaxis');
spectrogram(y,kaiser(256,10),220,1024,Fs,'yaxis');
colormap(cmap);
xlabel('Время')
ylabel('Частота')
end

