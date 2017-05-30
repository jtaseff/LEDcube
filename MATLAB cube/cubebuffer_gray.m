function cubebuffer_gray()
% updates front (transfer) buffer using grayscale data
% there's a sister function for standard / binary data


global cube;

% TODO - add grayscale logic here
cube.fb = cube.bb;

if cube.gsframe >= 2
	cube.fb = cube.gb | cube.bb;
	cube.gsframe = 0;
end

cube.gsframe = cube.gsframe + 1;