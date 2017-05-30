function eff_sinewave()

global cube;
if ~isfield(cube, 'effdata')
	cube.effdata.type = 'none';
end
if ~strcmp(cube.effdata.type, 'sinewave')
	cube.effdata = struct;
	cube.effdata.type = 'sinewave';
	cube.effdata.frame = 0;
	cube.effdata.vals = zeros(8, 1);
	cube.effdata.mult = 15;
end
data = cube.effdata;

% rollover if needed
data.frame = data.frame + 1;
if data.frame > 360
	data.frame = 0;
end

% create the new value to tack on
newval = round((cosd(data.frame * data.mult) * -3.5) + 4.5);
data.vals = [data.vals(2:8); newval];

% draw the cube
cubeclear;
for ii = 1:8
	if data.vals(ii) < 1
		cube.bb(:, ii, 1) = 1;
	elseif data.vals(ii) > 8
		cube.bb(:, ii, 8) = 1;
	else
		cube.bb(:, ii, data.vals(ii)) = 1;
	end
end


% finish and update
cube.effdata = data;
cube.frame = cube.frame + 1;
cubebuffer;
cubeupdate;

end %function














