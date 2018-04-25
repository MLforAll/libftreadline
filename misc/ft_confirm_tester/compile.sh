#!/bin/sh -e

make -C ../../libft
make -C ../..
gcc ft_confirm_tester.c -I ../../includes -I ../../libft -L ../.. -L ../../libft -lftreadline -lft -ltermcap
