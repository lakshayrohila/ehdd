#!/bin/sh

# this script is called after 'set_version.sh'

cd src/

sed -i 's/^#define VERSION .*$/#define VERSION "version undefined"/g' version_def.h

cd ..
