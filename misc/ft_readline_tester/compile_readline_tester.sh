#!/bin/sh -e

if [ ! -f ft_readline_tester.c ]; then
	echo "OOPS!"
	echo "Not in right folder!"
	echo "You are here: $PWD"
	exit 1
fi

librlp="../.."
libftp="../../libft"

make -C "$libftp"
make -C "$librlp"
gcc -o ft_readline_tester ft_readline_tester.c -I "$libftp/includes" -I "$librlp/includes" -L "$libftp" -L "$librlp" -lft -lftreadline -ltermcap
