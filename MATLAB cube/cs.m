function cs(sec)
% sets up and starts timer

if nargin < 1
	sec = 60;
end
global cube;
if isfield(cube, 'timer')
	if isvalid(cube.timer)
		if strcmp(cube.timer.Running, 'on')
			disp('Timer already running');
			return;
		end
	end
end

t = timer;
t.StartFcn = @cubetimer_start;
t.StopFcn = @cubetimer_cleanup;
t.TimerFcn = @cubecallback;
t.Period = 0.03;
t.ExecutionMode = 'fixedSpacing';
t.TasksToExecute = ceil(sec/t.Period);
cube.timer = t;
start(cube.timer)


	function cubetimer_start(~, ~)
		disp(['Starting cube for ', num2str(sec), ' sec']);
	end

	function cubetimer_cleanup(timerinst, ~)
		disp('Stopping cube');
		delete(timerinst);
	end

end