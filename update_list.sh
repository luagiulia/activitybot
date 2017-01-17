applicationPath="/Users/lucagiuliani/Documents/UCL/COMP105P (Robots)/Simulator/Client/applications/"
cmakeListPath="/Users/lucagiuliani/Documents/UCL/COMP105P (Robots)/Simulator/Client/applications/CMakeLists.txt"
directory="my_apps/"

#depending on your machine but avoids an error message
echo "cmake_minimum_required(VERSION 3.5)" > "${cmakeListPath}"

#the one that was already here
echo "DECLARE_APP(spinLeftRight spinLeftRight.c)" >> "${cmakeListPath}"

#get the paths and append to the file
for i in $(ls -d */); do
	for f in ${i}* ; do
		path=$directory$f
		name=${f%%.*}
		name=${name#*/}
		echo "DECLARE_APP(${name} ${path})" >> "${cmakeListPath}"
	done
done

#this considers that your apps directory is in the simulator directory
cd "$applicationPath"
cmake .
make