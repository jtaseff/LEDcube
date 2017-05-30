function ret = eff_rain(ser, iter)

speed = 0.075;


mat = zeros(8,8,8);
r = randi([0, 3], [1, iter]);

for iter = 1:iter
    for drops = 1:r(iter)
        pos = randi([1,8], [1,2]);
        mat(pos(1), pos(2), 1) = 1;
    end
    cubesend(cubeparse(mat), ser);
    pause(speed);
    mat = circshift(mat, [0, 0, 1]);
    mat(:,:,1) = 0;
    
end

%nice ending
for iter = 1:8
    cubesend(cubeparse(mat), ser);
    pause(speed);
    mat = circshift(mat, [0, 0, 1]);
    mat(:,:,1) = 0;
end



ret = 1;
end%function