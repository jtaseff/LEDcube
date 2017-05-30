function cubeclear()
% clear the back buffer of the cube (for std or gray data)

global cube;
cube.bb = zeros(8, 8, 8);
cube.gb = zeros(8, 8, 8);
