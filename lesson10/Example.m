%% Построение спектра сигнала
clc; clear;
fs = 100;                                % sample frequency (Hz)
t = 0:1/fs:10-1/fs;                      % 10 second span time vector
x = (1.3)*sin(2*pi*15*t) ...             % 15 Hz component
  + (1.7)*sin(2*pi*40*(t-2));            % 40 Hz component
PlotFFT(x,fs);

%% Меандр

clc; clear;
hold on;
f1 = 10; 
fd = 1000; 
w1 = 2*pi*f1/fd; 
a1 = 4/pi;
t = 0 : 250;
x1 = sin(w1*t);
x3 = 1/3*sin(3*w1*t);
x5 = 1/5*sin(5*w1*t);
x7 = 1/7*sin(7*w1*t);
x9 = 1/9*sin(9*w1*t);
x_sum = a1*(x1 + x3 + x5 + x7 + x9);
plot(t, x1);
plot(t, x3);
plot(t, x5);
plot(t, x7);
plot(t, x9);
plot(t, x_sum);
PlotFFT(x_sum,fd);

%% Меандр N
close all;
clc; clear;
N = 3*100;
f1 = 10; 
fd = 1000; 
w1 = 2*pi*f1/fd; 
a1 = 4/pi;
t = 0 : 250;
x = 0;
for i=1:2:N
    x = x + (1/i)*sin(i*w1*t);
end
x_sum_N = a1*(x);
plot(t, x_sum_N);
PlotFFT(x_sum_N,fd);

%% Построение сонограммы

clc
clear;
N_letters = 19;
N_birds = 2;
Fs=44100;
[y,fs] = audioread('Voices cut\sinsca1.wav');
y=y(:,1);
x = round(birdspectr(y,Fs));
[y,fs] = filter_song(y,fs,x-2000,x+2000);
figure()
spectrogram(y,kaiser(256,10),220,1024,Fs, 'yaxis');
birdsonogram(y,Fs);

%% Свертка
t = 0 : 250;
N = 500;
N_s = 0;
f1 = sin(2*pi*t/N);
f2 = sin((2*pi*(t + N_s))/N);
A = conv(f1,f1);
max(A)
plot(A);



%% Генерация массива
clc; clear;
shag = 0.2;
p = -1;
for i=-1 + shag:shag:1
p = [p i];
end
p = [p ; p];
z = func(p(1,:),p(2,:));

%nftool
%% Проверка полученного массива
clc; 
shag = 0.33;
p = -1;
for i=-1 + shag:shag:1
p = [p i];
end
p = [p ; p];
z = func(p(1,:),p(2,:));

err = abs(myNeuralNetworkFunction(p(1,:),p(2,:)) - z)
Max_err = max(err)

