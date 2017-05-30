function parseout = cubeparse(mat)

    parseout = zeros(8, 8);
    
    for ii = 1:8
        for jj = 1:8
            parseout(jj, ii) = bi2de_hobbled(mat(:, ii, jj)');
        end
        
    end

end