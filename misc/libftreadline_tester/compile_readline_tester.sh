#!/bin/sh -e

if [ ! -f libftreadline_tester.c ]; then
	echo "OOPS!"
	echo "Not in right folder!"
	echo "You are here: $PWD"
	exit 1
fi

librlp="../.."
libftp="../../libft"

make -C "$libftp"
make -C "$librlp"
gcc -o libftreadline_tester libftreadline_tester.c -I "$libftp" -I "$librlp/includes" -L "$libftp" -L "$librlp" -lft -lftreadline -ltermcap
