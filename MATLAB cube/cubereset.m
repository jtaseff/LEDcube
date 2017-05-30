function cubereset()

global cube
try
	stop(cube.timer);
end
try
	fclose(cube.ser);
end
try
	clear cube.ser;
end
try
	delete(instrfindall);
end

end 