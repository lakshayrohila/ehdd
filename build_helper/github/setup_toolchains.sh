#!/bin/sh

# |--------------------------------------------------------------------------
# | Compilers have been received from https://github.com/dimkr/toolchains.  |
# | Thanks to the developers of toolchains for the software!                |
# |--------------------------------------------------------------------------

# This script setups the compilers to be used received from toolchains.
#
# The code itself is split into three:-
#   1. Code to check for available update ('-c' cmd line option)
#   2. Code to download available update ('-d' cmd line option) -- ran only
#      when '-c' returned with code '0'.
#   3. Code to install toolchains ('-i' cmd line option)

# GitHub REST API is used to read JSON data for latest toolchains release.
LATEST_API_URL="https://api.github.com/repos/dimkr/toolchains/releases/latest"

# 'TOOLCHAINS_PACKED_SAVE_DIR' will be cached on GitHub workflow runs.
# Get the cached dirs if present, otherwise create new.
TOOLCHAINS_PACKED_SAVE_DIR="../toolchains_packed"
EHDD_DIR="$(dirname "$(readlink -f "$0")")"

LATEST_TOOLCHAINS_TAG="$(curl -s "$LATEST_API_URL" | grep "tag_name" | cut -d: -f2 | cut -d\" -f2)"

cd "$TOOLCHAINS_PACKED_SAVE_DIR"

case $1 in
-c)
	UPDATE_AVAILABLE=0

	if [ ! -f ./toolchains_tag.metadata ]; then
		echo 'NEW FILE' > ./toolchains_tag.metadata
		UPDATE_AVAILABLE=1
	fi

	if [ "$LATEST_TOOLCHAINS_TAG" != "$(cat ./toolchains_tag.metadata)" ]; then
		rm -rf ./*
		UPDATE_AVAILABLE=1
	fi

	if [ $UPDATE_AVAILABLE -eq 1 ]; then
		touch $EHDD_DIR/toolchains.update_available
	fi
	;;
-d)
	TC_DOWNLOADS_URLS="$(curl -s "$LATEST_API_URL" | grep "browser_download_url" | cut -d: -f2,3 | tr -d \")"

	echo "wget -t 3 $TC_DOWNLOADS_URLS"

	wget -t 3 $TC_DOWNLOADS_URLS || { printf "wget failed: Please read above errors.\nExiting!\n"; exit 1; }

	echo "$LATEST_TOOLCHAINS_TAG" > ./toolchains_tag.metadata
	;;
-i)
	for tar_pkg in *.tar.gz; do
		[ ! -f "$tar_pkg" ] && { printf "No *.tar.gz found.\nExiting\n"; exit 1; }

		CURR_COMP=$(echo "$tar_pkg" | cut -d. -f1)
		COMPILERS_LIST="$COMPILERS_LIST$CURR_COMP\n"

		sudo tar -xzf "$tar_pkg" -C /
	done

	printf "$COMPILERS_LIST" > "./compilers_list.metadata"
	;;
esac

cd $EHDD_DIR
exit 0
