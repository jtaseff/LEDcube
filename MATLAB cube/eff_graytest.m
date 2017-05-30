function eff_graytest

global cube;
if ~isfield(cube, 'effdata')
	cube.effdata.type = 'none';
end
if ~strcmp(cube.effdata.type, 'graytest')
	cube.effdata = struct;
	cube.effdata.type = 'graytest';
	cube.effdata.frame = 0;
end

cube.bb(1, 1, 1) = 1;
cube.bb(1, 2, 1) = 1;
cube.bb(2, 1, 1) = 1;
cube.bb(2, 2, 1) = 1;
cube.bb(1, 1, 2) = 1;
cube.bb(1, 2, 2) = 1;
cube.bb(2, 1, 2) = 1;
cube.bb(2, 2, 2) = 1;

cube.gb(4, 1, 1) = 1;
cube.gb(4, 2, 1) = 1;
cube.gb(5, 1, 1) = 1;
cube.gb(5, 2, 1) = 1;
cube.gb(4, 1, 2) = 1;
cube.gb(4, 2, 2) = 1;
cube.gb(5, 1, 2) = 1;
cube.gb(5, 2, 2) = 1;

cubebuffer_gray;
cubeupdate;

end