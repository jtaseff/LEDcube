function cubecallback(timerinst, ~)
% state machine for cube

global cube;
if ~isfield(cube, 'state')
	cube.state = 0;
end

if cube.state > 0
	% main state machine here
	% calls effect function to update buffer, then updates frame to cube
	
	switch cube.state
		case 1
			eff_snake();
		case 2
			eff_rain();
		case 3
			eff_planeboing();
		case 4
			eff_sinewave();
		case 5
			eff_sinewave3d();
		case 6
			eff_rain();
			
			
		otherwise
			cube.state = 0;
	end
	


else
	disp('No state selected');
	stop(timerinst);	% if we drop out of the machine, stop the timer
end
