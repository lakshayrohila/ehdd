#!/bin/sh

cd src/

sed -i 's/^#define VERSION .*$/#define VERSION "compiled on '"$(date +%d-%m-%Y)"'"/g' version_def.h

cd ..
