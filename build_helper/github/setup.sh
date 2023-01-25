#!/bin/sh

# this script is called by a GitHub workflow run.
# read 'README.dir' for more information

# set version
VERSION="$1"
sed -i 's/#define VERSION "version undefined"/#define VERSION "version '"$VERSION"'"/g' ./src/version_def.h

# setup build dirs
EHDD_DIR="$(pwd)"
HELPER_DIR="./build_helper/github"
BUILD_DIR_PRE="./ehdd-v$1"
TO_DIRS=$(cat "../toolchains_packed/compilers_list.metadata" | cut -d'-' -f1)

cd "$HELPER_DIR/src/"
for symlink in $(find . -type l); do
	target=$(readlink "$symlink")
	rm "$symlink"
	cp -r "$target" ./
done

find ./ -type f -name '*.md' -exec sed -i 's/_@EHDD_VERSION_/'"$VERSION"'/g' "{}" \;

FIGLET_OUTPUT="$(figlet -f script ehdd - v$VERSION -w 100 | sed '/^[[:space:]]*$/d' && echo)" \
ruby -p -i -e "gsub('_@FIGLET_OUTPUT_', ENV['FIGLET_OUTPUT'])" README.md

cd "$EHDD_DIR"

for dir in $TO_DIRS; do
	mkdir -p "$BUILD_DIR_PRE-$dir/usr/bin"
	cp -r $HELPER_DIR/src/* "$BUILD_DIR_PRE-$dir"

	find "$BUILD_DIR_PRE-$dir" -type f -name '*.md' -exec sed -i 's/_@EHDD_ARCHITECTURE_/'"$dir"'/g' "{}" \;
done
