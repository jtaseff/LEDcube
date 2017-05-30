function ret = eff_planescroll(ser, iter)

speed = 0.05;

%scroll in X
mat = zeros(8,8,8);
mat(1,:,:) = 1;
for ii = 1:iter*8 - 1
    cubesend(cubeparse(mat), ser);
    pause(speed);
    mat = circshift(mat, [1, 0, 0]);
end
for ii = 1:iter*8
    cubesend(cubeparse(mat), ser);
    pause(speed);
    mat = circshift(mat, [-1, 0, 0]);
end

%scroll in Y
mat = zeros(8,8,8);
mat(:,1,:) = 1;
for ii = 1:iter*8
    cubesend(cubeparse(mat), ser);
    pause(speed);
    mat = circshift(mat, [0, 1, 0]);
end

%scroll in Z
mat = zeros(8,8,8);
mat(:,:,1) = 1;
for ii = 1:iter*8
    cubesend(cubeparse(mat), ser);
    pause(speed);
    mat = circshift(mat, [0, 0, 1]);
end




ret = 1;
end %function