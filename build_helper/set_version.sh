#!/bin/sh

read -p "Set version: " VERSION

if [ -n "${VERSION}" ] ; then
	sed -i 's/#define VERSION "version undefined"/#define VERSION "version '"$VERSION"'"/g' src/version_def.h
else
	sed -i 's/#define VERSION "version undefined"/#define VERSION "compiled on '"$(date +%d-%m-%Y)"'"/g' src/version_def.h
fi
