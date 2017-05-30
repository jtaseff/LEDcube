function ret = gfx_slice(position)
% generates a slice of a 8x8x8 matrix in the normal/position [x y z]

ret = zeros(8, 8, 8);

if position(1) > 0
	ret(position(1), :, :) = 1;
end
if position(2) > 0
	ret(:, position(2), :) = 1;
end
if position(3) > 0
	ret(:, :, position(3)) = 1;
end


