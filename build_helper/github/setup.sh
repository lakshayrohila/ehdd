#!/bin/sh

# this script is called by a GitHub workflow run.
# read 'README.dir' for more information

HELPER_DIR="./build_helper/github"
BUILD_DIR_PRE="./ehdd-v$1"

makedir() {
	mkdir -p $BUILD_DIR_PRE-$1/usr/bin
	cp $HELPER_DIR/src/* $BUILD_DIR_PRE-$1
}

makedir "x86_64"		# dynamic
makedir "x86"			#  ones

makedir "x86_64-static"		# static
makedir "x86-static"		#  ones
