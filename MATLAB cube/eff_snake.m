function eff_snake()
% simple snaking animation to demonstrate update rate

global cube;
if ~isfield(cube, 'effdata')
	cube.effdata.type = 'none';
end
if ~strcmp(cube.effdata.type, 'snake')
	cube.effdata = struct;
	cube.effdata.type = 'snake';
	cube.effdata.frame = 0;
	cube.effdata.length = 5;
	cube.effdata.dist = [1 1 1 2 2 2 3 3 3 4 4 5 6 7 8];
	cube.effdata.pixels = 4*ones(cube.effdata.length, 3);
	cube.effdata.currvec = [0, 0, 0];
	cube.effdata.pixels2 = 4*ones(cube.effdata.length, 3);
	cube.effdata.currvec2 = [0, 0, 0];
	cube.effdata.frame2 = 0;
end

neednew = checkintowall(cube.effdata.currvec, cube.effdata.pixels);
if cube.effdata.frame <= 0
	neednew = neednew + 1;
end

% choose a new direction - random turn, no backtrack or continue straight
if neednew
	% make a new duration (twice as likely to get 2 or 3)
	cube.effdata.frame = cube.effdata.dist(randi(length(cube.effdata.dist), 1));
	if cube.effdata.frame > 8
		cube.effdata.frame = cube.effdata.frame - 7;
	end
	
	checkdir = 0;
	while checkdir <= 0
		checkdir = 1;
		newvec = makenewdir;
		
		% check that it's not in the same or opposite direction
		if abs(newvec) == abs(cube.effdata.currvec)
			checkdir = -1;
		end
		
		% check that it's not pointing into a wall
		wallcheck = checkintowall(newvec, cube.effdata.pixels);
		if wallcheck > 0
			newvec = newvec * -1;
			wallcheck = checkintowall(newvec, cube.effdata.pixels);
			if wallcheck > 0
				checkdir = -2;
			end
		end
		
	end
	cube.effdata.currvec = newvec;
end

% update the data using the current direction vector, shift pixels down
cube.effdata.pixels = [
	cube.effdata.pixels(1, :) + cube.effdata.currvec;
	cube.effdata.pixels(1:cube.effdata.length-1, :)
	];

% do it all again for snake 2!
neednew = checkintowall(cube.effdata.currvec2, cube.effdata.pixels2);
if cube.effdata.frame2 <= 0
	neednew = neednew + 1;
end

% choose a new direction - random turn, no backtrack or continue straight
if neednew
	% make a new duration (twice as likely to get 2 or 3)
	cube.effdata.frame2 = randi(10, 1);
	if cube.effdata.frame2 > 8
		cube.effdata.frame2 = cube.effdata.frame2 - 7;
	end
	
	checkdir = 0;
	while checkdir <= 0
		checkdir = 1;
		newvec = makenewdir;
		
		% check that it's not in the same or opposite direction
		if abs(newvec) == abs(cube.effdata.currvec2)
			checkdir = -1;
		end
		
		% check that it's not pointing into a wall
		wallcheck = checkintowall(newvec, cube.effdata.pixels2);
		if wallcheck > 0
			checkdir = -2;
		end
		
	end
	cube.effdata.currvec2 = newvec;
end

% update the data using the current direction vector, shift pixels down
cube.effdata.pixels2 = [
	cube.effdata.pixels2(1, :) + cube.effdata.currvec2;
	cube.effdata.pixels2(1:cube.effdata.length-1, :)
	];



% turn on pixels
cubeclear;
for ii = 1:cube.effdata.length
	subcell = num2cell(cube.effdata.pixels(ii,:));
	cube.bb(subcell{:}) = 1;
	% again for snake 2
	subcell = num2cell(cube.effdata.pixels2(ii,:));
	cube.bb(subcell{:}) = 1;
end

% wrap up
cube.effdata.frame = cube.effdata.frame - 1;	% direction counter
cube.effdata.frame2 = cube.effdata.frame2 - 1;	% direction counter
cube.frame = cube.frame + 1;
cubebuffer;	% back buffer to front
cubeupdate;
end


function newvector = makenewdir()
	newdir = randi(6, 1);	% to choose new direction
	switch mod(newdir, 3)
		case 0
			newvector = [1 0 0];
		case 1
			newvector = [0 1 0];
		case 2
			newvector = [0 0 1];
	end
	if newdir > 3
		newvector = -1 * newvector;
	end
end

function intowall = checkintowall(vec, pixels)
	intowall = 0;
	if isequal(vec, [1 0 0]) && pixels(1, 1) == 8
		intowall = intowall + 1;
	end
	if isequal(vec, [-1 0 0]) && pixels(1, 1) == 1
		intowall = intowall + 1;
	end
	if isequal(vec, [0 1 0]) && pixels(1, 2) == 8
		intowall = intowall + 1;
	end
	if isequal(vec, [0 -1 0]) && pixels(1, 2) == 1
		intowall = intowall + 1;
	end
	if isequal(vec, [0 0 1]) && pixels(1, 3) == 8
		intowall = intowall + 1;
	end
	if isequal(vec, [0 0 -1]) && pixels(1, 3) == 1
		intowall = intowall + 1;
	end
end

