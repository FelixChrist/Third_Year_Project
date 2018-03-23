Filename = 'Resistance2.xlsx';
excelrange = 'A2:E50';
data = xlsread(Filename, excelrange);
x = data(:,1)
y = data(:,5)

semilogx(x,y);