function eff_boxboing()

global cube;
if ~isfield(cube, 'effdata')
	cube.effdata.type = 'none';
end
if ~strcmp(cube.effdata.type, 'boxboing')
	cube.effdata = struct;
	cube.effdata.type = 'boxboing';
	cube.effdata.frame = 0;
	cube.effdata.dest = 0;
end

data = cube.effdata;






cube.effdata = data;
cube.frame = cube.frame + 1;
cubebuffer;
cubeupdate;

end %function













