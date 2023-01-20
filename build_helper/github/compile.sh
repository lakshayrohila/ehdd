#!/bin/sh

# this script is called by a GitHub workflow run.
# read 'README.dir' for more information

HELPER_DIR="./build_helper/github"
BUILD_DIR_PRE="./ehdd-v$1"

CC_SUFFIX="src/main.c -Wall -Wextra -Werror $CFLAGS $LDFLAGS"
#        . "/opt/x-tools/$CURR_COMP/activate"
compile() {
	$1 $CC_SUFFIX -o $BUILD_DIR_PRE-`cut -d'-' -f1 <<< $1`/usr/bin/ehdd

	if [ $? -ne 0 ]; then
		echo "Compilation failed: gcc returned with error"
		exit 1
	fi
}

compile "x86_64" "64" "x86_64"
compile "i386" "32" "x86"
