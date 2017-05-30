function data = gfx_shift(data, position, wrap)
% generates a slice of a 8x8x8 matrix in the direction [x y z]

if nargin < 3
	wrap = 0;
end
if nargin < 2
	error('Invalid input')
end


if position(1) > 0
	if wrap
		wrapdata = data(end-position(1):end, :, :);
	end
	data = 0;
end

