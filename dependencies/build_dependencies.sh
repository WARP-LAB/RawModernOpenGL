#!/bin/bash
# written by kroko @ WARP

echo "This will dowload GLEW and GLFW and build DYLIBS"

command -v cmake >/dev/null 2>&1 || {
  echo >&2 "Cmake is only not OOB stuff required to build this (well, apart from compiler :)). Please do brew install cmake. Aborting."
  # echo -e "\xE2\x9B\x94"
  echo ❌❌❌❌❌❌❌❌
  exit 1
}

# https://stackoverflow.com/a/3572105/1979530
realpath() {
    [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

PATH_START=$(pwd)
PATH_SCRIPT=$(realpath $0)
PATH_DEP=$(dirname $PATH_SCRIPT)

# Just clean up previous stuff if exists
rm -rf $PATH_DEP/glew
rm -rf $PATH_DEP/glfw
rm -rf $PATH_DEP/tmp

# ################################################################
# Build GLEW

echo 🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷
echo "Starting GLEW ..."

PATH_GLEW_BASE=$PATH_DEP/tmp/glew
PATH_GLEW_BUILD=$PATH_DEP/tmp/glew/build
mkdir -p $PATH_GLEW_BASE

cd $PATH_GLEW_BASE
curl -LO https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0.zip > glew-2.1.0.zip
unzip glew-2.1.0.zip
cd glew-2.1.0
# http://glew.sourceforge.net/build.html
make GLEW_DEST=$PATH_GLEW_BUILD OPT="-march=native -O2" install
# change LC_ID_DYLIB for dylib to something else not absolute path
#install_name_tool -id "lib/libGLEW.2.1.0.dylib" $PATH_GLEW_BUILD/lib/libGLEW.2.1.0.dylib
install_name_tool -id "@executable_path/../Frameworks/libGLEW.2.1.0.dylib" $PATH_GLEW_BUILD/lib/libGLEW.2.1.0.dylib
rm -rf $PATH_DEP/glew
mv $PATH_GLEW_BUILD $PATH_DEP/glew

echo "... GLEW phase ended."

# ################################################################
# Build GLFW

echo 🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷
echo "Starting GLFW ..."

PATH_GLFW_BASE=$PATH_DEP/tmp/glfw
PATH_GLFW_BUILD=$PATH_DEP/tmp/glfw/build
mkdir -p $PATH_GLFW_BASE

cd $PATH_GLFW_BASE
curl -LO https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip > glfw-3.2.1.zip
unzip glfw-3.2.1.zip
cd glfw-3.2.1
# http://www.glfw.org/docs/latest/compile.html#compile_options
# remove -DBUILD_SHARED_LIBS=ON if you want static lib
cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=$PATH_GLFW_BUILD .
make
make install
install_name_tool -id "@executable_path/../Frameworks/libglfw.3.2.dylib" $PATH_GLFW_BUILD/lib/libglfw.3.2.dylib
mv $PATH_GLFW_BUILD $PATH_DEP/glfw

echo "... GLFW phase ended."

echo 🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷

rm -rf $PATH_DEP/tmp

echo 🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠

cd $PATH_START
