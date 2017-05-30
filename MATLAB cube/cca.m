function cca()
% cube clear all - clears buffers, sends blank data

global cube;
try
	cubestop;
end
cube.fb = zeros(8, 8, 8);
cube.bb = zeros(8, 8, 8);
cube.gb = zeros(8, 8, 8);
cubeupdate;
cube.effdata.type = 'none';
