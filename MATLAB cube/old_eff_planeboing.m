function ret = eff_planeboing(ser, numiter, dir)

speed = 0.01;

%scroll in X
mat = zeros(8,8,8);


if dir == 1
    mat(1,:,:) = 1;
    cubesend(cubeparse(mat), ser);
    for iter = 1:numiter
        for ii = 1:7
                    pause(speed);
            mat = circshift(mat, [1, 0, 0]);
            cubesend(cubeparse(mat), ser);
        end
        for ii = 1:7
            pause(speed);
            mat = circshift(mat, [-1, 0, 0]);
            cubesend(cubeparse(mat), ser);
        end
    end
elseif dir == 2
    mat(:,1,:) = 1;
    cubesend(cubeparse(mat), ser);
    for iter = 1:numiter
        for ii = 1:7
                    pause(speed);
            mat = circshift(mat, [0, 1, 0]);
            cubesend(cubeparse(mat), ser);
        end
        for ii = 1:7
            pause(speed);
            mat = circshift(mat, [0, -1, 0]);
            cubesend(cubeparse(mat), ser);
        end
    end
elseif dir == 3
        mat(:,:,1) = 1;
    cubesend(cubeparse(mat), ser);
    for iter = 1:numiter
        for ii = 1:7
                    pause(speed);
            mat = circshift(mat, [0, 0, 1]);
            cubesend(cubeparse(mat), ser);
        end
        for ii = 1:7
            pause(speed);
            mat = circshift(mat, [0, 0, -1]);
            cubesend(cubeparse(mat), ser);
        end
    end
end


ret = 1;
end %function