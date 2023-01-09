#!/bin/sh

# this script is called by a GitHub workflow run.
# read 'README.dir' for more information

HELPER_DIR="./build_helper/github"
BUILD_DIR_PRE="./ehdd-v$1"

CC="gcc src/main.c -Wall -Wextra -Werror"

compile() {
	$CC -m$1 -o $BUILD_DIR_PRE-$2/usr/bin/ehdd

	if [ $? -ne 0 ]; then
		echo "Compilation failed: gcc returned with error"
		exit 1
	fi
}

compile "64" "x86_64"		# dynamic
compile "32" "x86"		#  ones

compile "64 -static" "x86_64-static"	# static
compile "32 -static" "x86-static"	#  ones
