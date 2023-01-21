#!/bin/sh

# this script is called by a GitHub workflow run.
# read 'README.dir' for more information

# set version
sed -i 's/#define VERSION "version undefined"/#define VERSION "version '"$1"'"/g' ./src/version_def.h

# setup build dirs
HELPER_DIR="./build_helper/github"
BUILD_DIR_PRE="./ehdd-v$1"
TO_DIRS=$(cat "../toolchains_packed/compilers_list.metadata" | cut -d'-' -f1)

for dir in $TO_DIRS; do
	mkdir -p "$BUILD_DIR_PRE-$dir/usr/bin"
	cp $HELPER_DIR/src/* "$BUILD_DIR_PRE-$dir"
done
