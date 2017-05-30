function ret = eff_planeboingcross(ser, numiter)

speed = 0.05;

mat = zeros(8,8,8);
mat(1, :, :) = 1;
mat(:, 1, :) = 1;
mat(:, :, 1) = 1;
cubesend(cubeparse(mat), ser);
pause(speed);

for iter = 1:numiter
    for ii = 1:7
        mat = circshift(mat, [1,1,1]);
        cubesend(cubeparse(mat), ser);
        pause(speed);
    end
    pause(speed);
    for ii = 1:7
        mat = circshift(mat, [-1,-1,-1]);
        cubesend(cubeparse(mat), ser);
        pause(speed);
    end
    pause(speed);
    
end


ret = 1;
end %function