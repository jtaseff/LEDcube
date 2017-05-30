function eff_rain()

global cube;
if ~isfield(cube, 'effdata')
	cube.effdata.type = 'none';
end
if ~strcmp(cube.effdata.type, 'rain')
	cube.effdata = struct;
	cube.effdata.type = 'rain';
	cube.effdata.frame = 0;
	cube.effdata.hard = 1;	% how hard it's raining. 1-4
	cubeclear;
end
data = cube.effdata;

% shift cube down
cube.bb = circshift(cube.bb, [0, 0, 1]);
cube.bb(:, :, 1) = 0;

% increment and add a new drop
data.frame = data.frame - 1;
if data.frame <= 0
	numrain = ceil(abs(0.7*data.hard*randn));
	data.frame = ceil(abs((4-data.hard)*randn));
	for ii=1:numrain
		xx = randi(8);
		yy = randi(8);
		cube.bb(xx, yy, 1) = 1;
	end
end

% switch rain intensity at random
if randi(100) == 1
	if data.hard == 1
		data.hard = 2;
	elseif data.hard == 4
		data.hard = 3;
	else
		if randi(2) == 1
			data.hard = data.hard + 1;
		else
			data.hard = data.hard - 1;
		end
	end
end

% finish and update
cube.effdata = data;
cube.frame = cube.frame + 1;
cubebuffer;
cubeupdate;

end %function














