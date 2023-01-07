#!/bin/sh

cd src/

cp version_def.h .version_def.h.bak
sed -i 's/#define VERSION "version undefined"/#define VERSION "compiled on '"$(date +%d-%m-%Y)"'"/g' version_def.h

cd ..
