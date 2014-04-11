function x = find_1_in_array(a)

for i = 1:length(a)
    if(a(i)==1)
        x = i;
    end
end

end