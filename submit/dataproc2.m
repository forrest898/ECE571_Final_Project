close all;
% Indicies used for all files that were open and read can be found in 
% the corresponding log_RAPSIAN and log_VMWOS files


% Times take from log files for energy calculations
vince_mem_times = [32.875 32.875 32.859375 32.875];
vince_rle_times = [34.78125 34.78125 34.78125 34.78125];
rasp_mem_times = [142.85 142.955 143.879 142.893];
rasp_rle_times = [120.9 120.93 122.19 122.274];

% open files
fileId = fopen('16GB_memtest', 'r');
vince_mem = fscanf(fileId, '%f');

fileId = fopen('250bench_rle', 'r');
vince_rle = fscanf(fileId, '%f');

fileId = fopen('raspianMem', 'r');
rasp_mem = fscanf(fileId, '%f');

fileId = fopen('raspianRLE', 'r');
rasp_rle = fscanf(fileId, '%f');

% Calculate power and energy for VMWOS memory benchmark

hold on;
vince_mem_pow(1) = sum(vince_mem(9:43));
vince_mem_pow(2) = sum(vince_mem(93:127));
vince_mem_pow(3) = sum(vince_mem(185:219));
vince_mem_pow(4) = sum(vince_mem(262:297));

vince_av_mem_pow(1) = mean(vince_mem(9:43));
vince_av_mem_pow(2) = mean(vince_mem(93:127));
vince_av_mem_pow(3) = mean(vince_mem(185:219));
vince_av_mem_pow(4) = mean(vince_mem(262:297));

vince_mem_en(1) = (vince_mem_pow(1))*vince_mem_times(1);
vince_mem_en(2) = (vince_mem_pow(2))*vince_mem_times(2);
vince_mem_en(3) = (vince_mem_pow(3))*vince_mem_times(3);
vince_mem_en(4) = (vince_mem_pow(4))*vince_mem_times(4);


mean(vince_mem_pow(1:4))
mean(vince_av_mem_pow(1:4))
mean(vince_mem_en(1:4))

% Calculate power and energy for VMWOS RLE benchmark

vince_rle_pow(1) = sum(vince_rle(10:45));
vince_rle_pow(2) = sum(vince_rle(191:226));
vince_rle_pow(3) = sum(vince_rle(270:305));
vince_rle_pow(4) = sum(vince_rle(385:420));

vince_av_rle_pow(1) = mean(vince_rle(10:45));
vince_av_rle_pow(2) = mean(vince_rle(191:226));
vince_av_rle_pow(3) = mean(vince_rle(270:305));
vince_av_rle_pow(4) = mean(vince_rle(385:420));

vince_rle_en(1) = (vince_rle_pow(1))*vince_rle_times(1);
vince_rle_en(2) = (vince_rle_pow(2))*vince_rle_times(2);
vince_rle_en(3) = (vince_rle_pow(3))*vince_rle_times(3);
vince_rle_en(4) = (vince_rle_pow(4))*vince_rle_times(4);


mean(vince_rle_pow(1:4))
mean(vince_av_rle_pow(1:4))
mean(vince_rle_en(1:4))


% Calculate power and energy for Raspbian memory benchmark

rasp_mem_pow(1) = sum(rasp_mem(122:265));
rasp_mem_pow(2) = sum(rasp_mem(299:442));
rasp_mem_pow(3) = sum(rasp_mem(493:637));
rasp_mem_pow(4) = sum(rasp_mem(707:850));

rasp_av_mem_pow(1) = mean(rasp_mem(122:265));
rasp_av_mem_pow(2) = mean(rasp_mem(299:442));
rasp_av_mem_pow(3) = mean(rasp_mem(493:637));
rasp_av_mem_pow(4) = mean(rasp_mem(707:850));

rasp_mem_en(1) = (rasp_mem_pow(1))*rasp_mem_times(1);
rasp_mem_en(2) = (rasp_mem_pow(2))*rasp_mem_times(2);
rasp_mem_en(3) = (rasp_mem_pow(3))*rasp_mem_times(3);
rasp_mem_en(4) = (rasp_mem_pow(4))*rasp_mem_times(4);


mean(rasp_mem_pow(1:4))
mean(rasp_av_mem_pow(1:4))
mean(rasp_mem_en(1:4))

% Calculate power and energy for Raspbian RLE benchmark

rasp_rle_pow(1) = sum(rasp_rle(113:234));
rasp_rle_pow(2) = sum(rasp_rle(376:496));
rasp_rle_pow(3) = sum(rasp_rle(528:650));
rasp_rle_pow(4) = sum(rasp_rle(676:798));

rasp_av_rle_pow(1) = mean(rasp_rle(113:234));
rasp_av_rle_pow(2) = mean(rasp_rle(376:496));
rasp_av_rle_pow(3) = mean(rasp_rle(528:650));
rasp_av_rle_pow(4) = mean(rasp_rle(676:798));

rasp_rle_en(1) = (rasp_rle_pow(1))*rasp_rle_times(1);
rasp_rle_en(2) = (rasp_rle_pow(2))*rasp_rle_times(2);
rasp_rle_en(3) = (rasp_rle_pow(3))*rasp_rle_times(3);
rasp_rle_en(4) = (rasp_rle_pow(4))*rasp_rle_times(4);


mean(rasp_rle_pow(1:4))
mean(rasp_av_rle_pow(1:4))
mean(rasp_rle_en(1:4))
%{
x = linspace(1, 48, (49));
plot(x, vince_mem(9:57,1), '-..');
x = linspace(1, 52, (53));
plot(x, vince_rle(268:320,1), '--');
v = vline(34,'b','Mem');
v = vline(37, 'r', 'RLE');
xlim([0 52]);
xlabel('Time');
ylabel('Watts');
title("VWMOS Combined Benchmarks");
legend('Memory Benchmark', 'RLE Benchmark');



%refline([52 0]);
figure();
hold on;
vince_rle_mem_pow(1) = mean(vince_rle(268:305));
x = linspace(1, 52, (53));
plot(x, vince_rle(268:320,1));
xlabel('Time');
ylabel('Watts');
title("VWMOS RLE Benchmark");

figure();
hold on;
grid on;
rasp_mem_pow(1) = mean(rasp_mem(298:442));
x = linspace(1, 162, (163));
plot(x, rasp_mem(298:460,1), '-..');
x = linspace(1, 143, (144));
plot(x, rasp_rle(527:670,1), '--');
ylim([1.9 2.95]);
vline(145, 'b', 'MEM');
vline(124, 'r', 'RLE');
xlabel('Time');
ylabel('Watts');

title("Raspian Combined Benchmarks");
legend('Memory Benchmark', 'RLE Benchmark');

%refline([52 0]);
figure();
rasp_rle_mem_pow(1) = mean(rasp_rle(527:650));
x = linspace(1, 143, (144));
plot(x, rasp_rle(527:670,1));
xlabel('Time');
ylabel('Watts');
title("Raspian OS RLE Benchmark");

%}
figure();
%set(gca,'FontSize',18) % Creates an axes and sets its FontSize to 18

subplot(2,2,1)
grid on;
x = linspace(1, 48, (49));
plot(x, vince_mem(9:57,1));

vline(34,'r');
set(gca,'FontSize',18) % Creates an axes and sets its FontSize to 18
xlabel('Time', 'FontSize', 22);
ylabel('Watts', 'FontSize', 22);
grid on;
title("VWMOS Memory Benchmark", 'FontSize', 22);

subplot(2,2,2)
x = linspace(1, 162, (163));
plot(x, rasp_mem(298:460,1));
ylim([1.85 2.95]);
xlim([0 166]);
vline(145, 'r');
set(gca,'FontSize',18) % Creates an axes and sets its FontSize to 18
xlabel('Time', 'FontSize', 22);
ylabel('Watts', 'FontSize', 22);
grid on;
title('Raspian Memory Benchmark', 'FontSize', 22);
%{
title('This is my plot', 'FontSize', 24);
xlabel('x axis', 'FontSize', 24);
text(x, y, 'Hey, look at this', 'FontSize', 24);
%}

subplot(2,2,3)
x = linspace(1, 52, (53));
plot(x, vince_rle(268:320,1));
set(gca,'FontSize',18) % Creates an axes and sets its FontSize to 18
xlabel('Time', 'FontSize', 22);
ylabel('Watts', 'FontSize', 22);vline(37, 'r');
xlim([0 55]);
grid on;
title("VWMOS RLE Benchmark", 'FontSize', 22);

subplot(2,2,4)
x = linspace(1, 143, (144));
plot(x, rasp_rle(527:670,1));
ylim([1.85 2.95]);
vline(124, 'r');
set(gca,'FontSize',18) % Creates an axes and sets its FontSize to 18
xlabel('Time', 'FontSize', 22);
ylabel('Watts', 'FontSize', 22);grid on;
title("Raspian RLE Benchmark", 'FontSize', 22);

figure();
subplot(2,2,[1 2]);
hold on;
x = linspace(1, 48, (49));
plot(x, vince_mem(9:57,1), '-..');
x = linspace(1, 52, (53));
plot(x, vince_rle(268:320,1), '--');
v = vline(34,'b','Mem');
v = vline(37, 'r', 'RLE');
xlim([0 46]);
set(gca,'FontSize',18) % Creates an axes and sets its FontSize to 18
xlabel('Time', 'FontSize', 22);
ylabel('Watts', 'FontSize', 22);
title("VWMOS Combined Benchmarks", 'FontSize', 22);
legend('Memory Benchmark', 'RLE Benchmark');
grid on;

subplot(2,2,[3,4]);
hold on;
x = linspace(1, 162, (163));
plot(x, rasp_mem(298:460,1), '-..');
x = linspace(1, 143, (144));
plot(x, rasp_rle(527:670,1), '--');
ylim([1.9 2.95]);
xlim([0 160]);
vline(145, 'b', 'MEM');
vline(124, 'r', 'RLE');
set(gca,'FontSize',18) % Creates an axes and sets its FontSize to 18
xlabel('Time', 'FontSize', 22);
ylabel('Watts', 'FontSize', 22);grid on;
title("Raspian Combined Benchmarks", 'FontSize', 22);
legend('Memory Benchmark', 'RLE Benchmark');





