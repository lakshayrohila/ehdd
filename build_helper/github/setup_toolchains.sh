#!/bin/sh

# |--------------------------------------------------------------------------
# | Compilers have been received from https://github.com/dimkr/toolchains.  |
# | Thanks to the developers of toolchains for the software!                |
# |--------------------------------------------------------------------------

# This script setups the compilers to be used received from toolchains.

# setup compilers to be used

echo "Setting up compilers to be used ....."

# GitHub REST API used. Read https://docs.github.com/rest/actions/artifacts
# for more information on downloading artifacts from GitHub.
LATEST_API_URL="https://api.github.com/repos/dimkr/toolchains/releases/latest"

LATEST_TOOLCHAINS_TAG=$(curl -s "$LATEST_API_URL" | grep "tag_name.*" | cut -d: -f2 | cut -d\" -f2)

# 'TOOLCHAINS_PACKED_SAVE_DIR' will be cached on GitHub workflow runs.
# Get the cached dirs if present, otherwise create new.
TOOLCHAINS_PACKED_SAVE_DIR="../toolchains_packed"
EHDD_DIR="$(dirname "$(readlink -f "$0")")"

cd "$TOOLCHAINS_PACKED_SAVE_DIR"

if [ ! -f "./toolchains_tag.metadata" ]; then
	echo '#### NEW FILE ####' > "./toolchains_tag.metadata"
fi

if [ "$LATEST_TOOLCHAINS_TAG" != `cat "./toolchains_tag.metadata"` ]; then
	DOWNLOADS_URLS=$(curl -s "$LATEST_API_URL" | grep "browser_download_url.*tar.gz" | cut -d: -f2,3 | tr -d \")

	wget $DOWNLOADS_URLS || { printf "wget failed: Please read above errors.\nExiting!\n"; exit 1; }

	echo "$LATEST_TOOLCHAINS_TAG" > "./toolchains_tag.metadata"
fi

for tar_pkg in *.tar.gz; do
	[ ! -f "$tar_pkg" ] && { printf "No *.tar.gz found.\nExiting\n"; exit 1; }

	CURR_COMP=$(echo "$tar_pkg" | cut -d. -f1)
	COMPILERS_LIST="$COMPILERS_LIST$CURR_COMP\n"

	sudo tar -xzvf "$tar_pkg" -C /
done

printf "$COMPILERS_LIST" > "./compilers_list.metadata"

cd $EHDD_DIR
