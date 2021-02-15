fileup = fopen('Data/dataUp.txt','r');
filedown = fopen('Data/dataDown.txt','r');

formatSpec = '%f %f %f';
sizeA = [3 Inf];

dataup = fscanf(fileup,formatSpec,sizeA);
datadown = fscanf(filedown,formatSpec,sizeA);

fclose(fileup);
fclose(filedown);

figure('name','Left Motor');
xlabel('PWM');
ylabel('RPM');
hold on;
plot(dataup(1,:), dataup(2,:), 'g');
plot(datadown(1,:), datadown(2,:), 'r');

figure('name','Right Motor');
xlabel('PWM');
ylabel('RPM');
hold on;
plot(dataup(1,:), dataup(3,:), 'g');
plot(datadown(1,:), datadown(3,:), 'r');