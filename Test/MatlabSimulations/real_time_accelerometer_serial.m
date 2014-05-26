%run('clean');
clear all;
close all;

s = serial('/dev/tty.usbserial-A9A1L7NV'); %assigns the object s to serial port

set(s, 'InputBufferSize', 256); %number of bytes in inout buffer
set(s, 'FlowControl', 'hardware');
set(s, 'BaudRate', 9600);
set(s, 'Parity', 'none');
set(s, 'DataBits', 8);
set(s, 'StopBit', 1);
set(s, 'Timeout',10);
%clc;

disp(get(s,'Name'));
prop(1)=(get(s,'BaudRate'));
prop(2)=(get(s,'DataBits'));
prop(3)=(get(s, 'StopBit'));
prop(4)=(get(s, 'InputBufferSize'));

disp(['Port Setup Done!!',num2str(prop)]);

fopen(s);   %opens the serial port
t=1;
disp('Running');
x1=0;
x2=0;
v=0;
c=200;
while(t < c)  %  t < c Runs for c cycles - if you cant see the symbol, it is "less than" sign. so while (t less than 200)
    
    a = fscanf(s,'%f'); %reads the data from the serial port and stores it to the matrix a
    
    a=max(a);  % in this particular example, I'm plotting the maximum value of the 256B input buffer
    
    v=(a/9.8);
    %x1 =[x1 a];  % Merging the value to an array, this is not very computationaly effective, as the array size is dynamic.
    %Consider pre allocation the size of the array to avoid this. But beware, You might loose some important
    %data at the end!
    
    x2 = [x2 v];
    
    %figure(1);
    %plot(x1);
    %axis auto;
    %grid on;
    %hold on;
    
    %figure(2);
    %plot(x2);
    %axis auto;
    %grid on;
    %hold on;
    
    
    disp([num2str(t),'th iteration - Acc : ',num2str(a), ' - Velocity: ', num2str(v)]);
    t=t+1;
    a=0;  %Clear the buffer
    %drawnow;
end

fclose(s); %close the serial port
