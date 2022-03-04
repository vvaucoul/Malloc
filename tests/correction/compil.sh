#!/bin/sh

NAME=$1
cd ../../ && make && cd -
gcc $NAME.c ../../libft_malloc_x86_64_Linux.so -I../../includes/ ../../42_PCC_LIBFT.a -o $NAME