clc;
clear; 
[alphabet, targets] = prprob; % встроеннный алфавит
[R,Q] = size(alphabet);
[S2,Q] = size(targets);
S1 = 13;  % число нейронов в скрытом слое
net = newff(minmax(alphabet),[S1 S2],{'logsig' 'logsig'},'traingdx'); % создание сети
net.LW{2,1} = net.LW{2,1}*0.01; % настройка весов слоев
net.b{2} = net.b{2}*0.01; % настройка векторов смещения
gensim(net);



%% Обучение в отсутствии шума
clc
P = alphabet;
T = targets;
% функция производительности сети: сумма среднеквадратичной % погрешности
net.performFcn = 'sse';
% целевая среднеквадратичная погрешность
net.trainParam.goal = 0.13;
% частота вывода результатов на экран
net.trainParam.show = 20;
% максимальное количество циклов обучения
net.trainParam.epochs = 3000;
% Константа импульса - относительная инерция в направлении обучения
net.trainParam.mc = 0.95;
% обучение сети net: tr - training record, P - input data, T - output data
[net,tr] = train(net,P,T);

%% обучение в присутствии шума
clc
% создаем копию сети
netn = net;
% целевая среднеквадратичная погрешность
netn.trainParam.goal = 0.5;
% максимальное число циклов обучения
netn.trainParam.epochs = 500;
% четыре копии целевых векторов
T = [targets targets targets targets];
for pass = 1:10
%две идеальные и две зашумленные копии алфавита 
P = [alphabet, alphabet, (alphabet + randn(R,Q)*0.03), (alphabet + randn(R,Q)*0.13)]; 
[netn,tr] = train(netn,P,T);
end

%% Повторное обучение в отсутствие шума
clc
netn.trainParam.goal = 0.05;
netn.trainParam.epochs = 700;
netn.trainParam.show = 5;
[netn, tr] = train(netn,P,T);


%% Проверка работы сети
clc
X = randi([1 26]);
fprintf("X = %d\n", X);
noisyK = alphabet(:,X) + randn(90,1)*0.2;
A2 = sim(net,noisyK);
A2 = compet(A2);
% получаем ответ
answer = find(compet(A2) == 1);
fprintf("A = %d\n", answer);

%% Проверка работы сети в цикле
clc;
N_errors = 0;
N_iters = 1000;
for i=1:N_iters
    X = randi([1 26]);
    noisyK = alphabet(:,X) + randn(90,1)*0.5;
    A2 = sim(net,noisyK);
    A2 = compet(A2);
    answer = find(compet(A2) == 1);
    if(answer ~= X)
        N_errors = N_errors + 1;
    end
end
A = (N_iters-N_errors)/N_iters*100;
fprintf("Точность = %2.1f%%\n", A);


%% Эффективность функционирования системы
clc
% диапазон шума: от 0 до 0.5 с шагом 0.05
noise_range = 0:.05:.5;
%100 векторов, на которых производится проверка
max_test = 100;
% сеть, обученная на идеальных последовательностях
network1 = [];
% сеть, обученная на зашумленных последовательностях
network2 = [];
T = targets;
%выполнить тест
for noiselevel = noise_range
errors1 = 0;
errors2 = 0;
for i=1:max_test
P = alphabet + randn(90,26)*noiselevel; %тест для сети 1 (обученной на идеальных последовательностях)
A = sim(net,P);
%наибольший элемент с выхода сети делает = 1, остальные = 0 
AA = compet(A);
% количество ошибок
errors1 = errors1 + sum(sum(abs(AA-T)))/2; %тест для сети 2 (обученной на зашумленных последовательностях) 
An = sim(netn,P);
AAn = compet(An);
errors2 = errors2 + sum(sum(abs(AAn-T)))/2; echo off;
end
% средние значения ошибок (100 последовательностей из 26 векторов целей) 
network1 = [network1 errors1/26/100];
network2 = [network2 errors2/26/100];
end
% график погрешности сетей от уровня входного шума
plot(noise_range, network1*100,'--',noise_range,network2*100);
title('Процент ошибочных классификаций');
xlabel('Уровень шума');
ylabel('Сеть 1 - - Сеть 2 ---');
