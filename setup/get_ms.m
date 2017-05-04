function [mean, sigma, weights] = get_ms(fn)
    % Get data from the file
    fid = fopen(fn,'r');
    line = fgetl(fid);
    in_data = [];
    
    % Extract data
    while ischar(line)
        val = str2double(line);
        if (~isnan(val))
            in_data = [in_data; val];
        end
        line = fgetl(fid);
    end
    fclose(fid);
    
    % Put the data into matrices to return
    num = size(in_data,1)/3;
    mean = in_data(1:num);
    sigma = in_data(num+1:num*2);
    weights = in_data(num*2+1:end);
end