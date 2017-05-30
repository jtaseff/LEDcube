function cubeupdate()
% cube is looking for serial data as follows:
% L#datadata, i.e. L1aaaaaaaa, to send the data for a layer
% U to update the cube's transfer buffer to draw buffer (async)

global cube;

cube.outdata = cubeparse(cube.fb);

for ii = 1:8
    fwrite(cube.ser, [76, ii-1, cube.outdata(ii,:)]);
end
fwrite(cube.ser, 85);

flushinput(cube.ser);
end