#!/bin/sh

# this script is called after 'set_version.sh'

cd src/
mv .version_def.h.bak version_def.h
cd ..
