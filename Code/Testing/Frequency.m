filename = 'FrequencyResponse.xlsx';
excelrange = 'A1:E47';
data = xlsread(filename,excelrange);
x = data(:,1);
y = data(:,5);
semilogx(x,y);
title('Frequency response of printed speaker');
xlabel('Frequency (Hz)');
ylabel('Sound Level (dB)');