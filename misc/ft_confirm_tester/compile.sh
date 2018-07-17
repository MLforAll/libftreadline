#!/bin/sh -e

make -C ../../libft
make -C ../..
gcc -o test_prgm ft_confirm_tester.c -I ../../includes -I ../../libft/includes -L ../.. -L ../../libft -lftreadline -lft -ltermcap
