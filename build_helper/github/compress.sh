#!/bin/sh

# this script is called by a GitHub workflow run.
# read 'README.dir' for more information

BUILD_DIR_PRE="./ehdd-v$1"

for build in $BUILD_DIR_PRE*/; do
        tar -czvf "$build.tar.gz" "$build"
done
