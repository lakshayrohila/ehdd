#!/bin/sh

# this script is called by a GitHub workflow run.
# read 'README.dir' for more information

BUILD_DIR_PRE="./ehdd-v$1"

mkdir buff

for build in $BUILD_DIR_PRE*/; do
        tar -czvf "buff/$build.tar.gz" "$build"
done

mv buff/* ./
