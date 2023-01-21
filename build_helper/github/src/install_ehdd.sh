#!/bin/sh

echo "Installing ehdd ..."

if ! command -v eject >/dev/null 2>&1; then
        echo "eject: command not found"
        exit 1
elif ! command -v udisksctl >/dev/null 2>&1; then
        echo "udisksctl: command not found"
	echo "Please install 'udisks2'."
        exit 1
fi

TO_COPY=$(ls -l | grep "^d" | rev | cut -d' ' -f1 | rev)

for i in $TO_COPY; do
	cp -r "./$i" /
done

echo "ehdd is now installed."
echo "Thanks for installation!"
echo
echo "Please read https://github.com/lakshayrohila/ehdd#readme for more information."
