#!/bin/sh

# this script is called by a GitHub workflow run.
# read 'README.dir' for more information

HELPER_DIR="./build_helper/github"
BUILD_DIR_PRE="./ehdd-v$1"

compress() {
	buff="$BUILD_DIR_PRE-$1"
        tar -czvf "$buff.tar.gz" "$buff/"
}

compress "x86_64"
compress "x86"
