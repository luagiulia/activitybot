# Use getopts (Adrian Frühwirth) 
# 	http://stackoverflow.com/questions/16483119/example-of-how-to-use-getopts-in-bash
# Bash arguments (Juergen Haas)
# 	https://www.lifewire.com/pass-arguments-to-bash-script-2200571
# -z 
# 	http://stackoverflow.com/questions/18096670/what-does-z-mean-in-bash

usage() { echo "Usage : $0 [-a <string : application path>] [-d <string : apps directory path>]" 1>&2;exit 1; }

while getopts ":a:d:" opt; do
	case "${opt}" in
		a) applicationPath="${OPTARG}/" ;;
		d) directory="${OPTARG}/" ;; 
		*) usage ;;
	esac
done

shift $((OPTIND-1))

# check if paths are null
if [ -z "${applicationPath}" ] || [ -z "${directory}" ]; then
    usage
fi

cmakeListPath="${applicationPath}CMakeLists.txt"

# depending on your machine but avoids an error message
echo "cmake_minimum_required(VERSION 3.5)" > "${cmakeListPath}"

# the one that was already here
echo "DECLARE_APP(spinLeftRight spinLeftRight.c)" >> "${cmakeListPath}"

# get the paths and append to the file
for i in $(ls -d */); do
	for f in ${i}* ; do
		echo $f
		path=${directory}${f}
		name=${f%%.*}
		name=${name#*/}
		echo "DECLARE_APP(${name} \"${path}\")" >> "${cmakeListPath}"
	done
done

cd "${applicationPath}"
cmake .
make