function PlotFFT(y,fd)
figure();
L = 20000;
NFFT = 2^nextpow2(L);
Y = abs(fft(y,NFFT))/L;
f = fd/2*linspace(0,1,NFFT/2+1);
plot(f,2*abs(Y(1:NFFT/2+1)))
xlabel('Frequency');
ylabel('Power');
end