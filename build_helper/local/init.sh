#!/bin/sh

# this is called by Makefile
# this sets up build using other build_helper scripts

PRE="./build_helper/local" # prefix to script

$PRE/set_version.sh
