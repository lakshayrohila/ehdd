#!/bin/sh

# this file is run after all jobs complete
# this is required to get the build-time 'gcc' and 'glibc' version

# compile program to show glibc version
PRE="./build_helper/github/test"
gcc-7 $PRE/get_glibc_version.c -o get_glibc_version

# print things
echo 'Builds successful! These are used for building:-
	gcc version: '`gcc-7 --version | grep gcc`'
      glibc version: '`./get_glibc_version`
