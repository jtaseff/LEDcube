function cubebuffer()
% updates back (draw) buffer onto front (transfer) buffer
% for standard / binary data
% there's a sister function for dealing with grayscale data

global cube;
cube.fb = cube.bb;