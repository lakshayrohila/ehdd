#!/bin/sh

# this script is called by a GitHub workflow run.
# read 'README.dir' for more information

BUILD_DIR_PRE="./ehdd-v$1"
TOOLCHAINS_COMPILERS=`cat "../toolchains_packed/compilers_list.metadata"`

CC_SUFFIX="src/main.c -Wall -Wextra -Werror"

for compiler in $TOOLCHAINS_COMPILERS; do
	CFLAGS=""
	LDFLAGS=""

	. /opt/x-tools/$compiler/activate

	TODO="$compiler-gcc $CC_SUFFIX $CFLAGS $LDFLAGS -o $BUILD_DIR_PRE-$(echo $compiler | cut -d'-' -f1)/usr/bin/ehdd"

	echo "$TODO"

	$TODO || { printf "compilation failed: Please read above errors.\nExiting!\n"; exit 1; }
done
