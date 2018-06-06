#!/bin/sh -e

if [ ! -f quittest.c ]; then
	echo "OOPS!"
	echo "Not in right folder!"
	echo "You are here: $PWD"
	exit 1
fi

librlp="../.."
libftp="../../libft"

make -C "$libftp"
make -C "$librlp"
gcc -o quittest quittest.c -I "$libftp/includes" -I "$librlp/includes" -L "$libftp" -L "$librlp" -lft -lftreadline -ltermcap
