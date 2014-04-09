function sensor_concept() 

while (1)
    
    global a b;
    global top bottom;
    global x1 x2 y1 y2 k m;
    top = 0;
    bottom = 0;
    
    a = [0 0 0 0 0 0 0 0 0];
    b = [0 0 0 0 0 0 0 0 0];

    a(randi(9)) = 1;
    b(randi(9)) = 1;

    
    top = find_in_array(a==1)-5;
    bottom = find_in_array(b==1)-5;

    y1 = -4;
    y2 = 4;

    x1 = bottom;
    x2 = top;

	k = (y2-y1)/(x2-x1);
    m = y2 - (x2*k);
    
    if isinf(k)
        
        clf;
        
        
        axis([-4 4 -4 4])
        subplot(2,1,1);
        axis([-4 4 -4 4])
        line([x1,x1],[-4,4]);
        axis([-4 4 -4 4])
        
        grid on
        
        axis([-4 4 -4 4])
        subplot(2,1,2);
        axis([-4 4 -4 4])
        line([x1,x1],[-4,4]);
        axis([-4 4 -4 4])
        
        grid on
    else
        
        x = linspace(-4, 4);
        y = (k*x) + m;
        
        subplot(2,1,1);
        plot(x,y);
        axis([-4 4 -4 4])
        
        grid on
        
        subplot(2,1,2);
        plot(x,-y);
        axis([-4 4 -4 4])
        
        grid on
        
    end

    pause(0.2);

end

end


function x = find_in_array(a)

    for i = 1:length(a)
    
        if (a(i)==1)
            
            x = i;
        end
    
    end


end