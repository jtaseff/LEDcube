function eff_planeboing()

global cube;
if ~isfield(cube, 'effdata')
	cube.effdata.type = 'none';
end
if ~strcmp(cube.effdata.type, 'planeboing')
	cube.effdata = struct;
	cube.effdata.type = 'planeboing';
	cube.effdata.subtype = '3bs4';	% number of planes + Bounce/Roll/End + Sync/Random/Onevector + number of reps
	cube.effdata.var = 0;
	cube.effdata.frame = 0;
	cube.effdata.pos = {[0, 0, 0]};
end

% if mod(cube.frame, 2) == 0
% 	cube.frame = cube.frame + 1;
% 	return;
% end

data = cube.effdata;

% check number of slices against desired, create new if no match
if length(data.pos) ~= str2double(data.subtype(1))
	data.pos = cell(str2double(data.subtype(1)), 1);
	for ii = 1:str2double(data.subtype(1))
		data.pos{ii} = [0 0 0];
	end
end

% populate with new starting positions
for ii = 1:length(data.pos)
	if isequal(data.pos{ii}, [0 0 0])
		newdir = randi(6);	% to choose new direction
		switch mod(newdir, 3)
			case 0
				data.pos{ii} = [1 0 0];
			case 1
				data.pos{ii} = [0 1 0];
			case 2
				data.pos{ii} = [0 0 1];
		end
		% randomly make some backwards
		if newdir > 3
			data.pos{ii} = -8 * data.pos{ii};
		end
		% TODO something for random starting positions
	end
end

% draw these positions
cubeclear;
for ii = 1:length(data.pos)
	cube.bb = cube.bb | gfx_slice(abs(data.pos{ii}));
end


% num = str2double(data.subtype(4));
% update positions for next frame
for ii = 1:length(data.pos)
	switch data.subtype(2)
		case {'B' 'b'} % bounce
			data.pos{ii} = bounceback(data.pos{ii});
		case {'R' 'r'} % rollover
			data.pos{ii} = rollover(data.pos{ii});
	end
end

% reset after a while to pick a new direction
data.frame = data.frame + 1;
if data.frame > str2double(data.subtype(4)) * 7;
	for ii = 1:length(data.pos)
		data.pos{ii} = [0 0 0];
	end
	data.frame = 0;
end

cube.effdata = data;
cube.frame = cube.frame + 1;
cubebuffer;
cubeupdate;

end %function



% helper functions

function pos = endstop(pos)
% only return true if any of the axes are at the end of travel in their dir
	for coord = 1:3
		if pos(coord) == 9 || pos(coord) == -1
			pos(coord) = 0;
		end
	end
end

function pos = rollover(pos)
% rolls over any positions at the end of their travel direction
	for coord = 1:3
		if pos(coord) == 8
			pos(coord) = 1;
		elseif pos(coord) == -1
			pos(coord) = -8;
		elseif pos(coord) ~= 0
			pos(coord) = pos(coord) + 1;
		end
	end
end

function pos = bounceback(pos)
% reverses any positions at theend of their travel direction
	for coord = 1:3
		if pos(coord) == 8
			pos(coord) = -8;
		elseif pos(coord) == -1
			pos(coord) = 1;
		elseif pos(coord) ~= 0
			pos(coord) = pos(coord) + 1;
		end
	end
end











