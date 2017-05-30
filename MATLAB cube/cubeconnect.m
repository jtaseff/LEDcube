function cubeconnect()

global cube
cube.ser = serial('COM3');
fopen(cube.ser);

cube.bb = zeros(8, 8, 8);	% front buffer
cube.fb = zeros(8, 8, 8);	% back buffer
cube.frame = 0;				% frame counter for animations, etc

cube.gb = zeros(8, 8, 8);	% grayscale (optional) buffer
cube.gsframe = 0;			% frame counter for grayscale data


end