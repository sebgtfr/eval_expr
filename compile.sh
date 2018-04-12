#!/bin/bash

COMPILER="gcc"
FLAGS="-w -Wall -Wextra -Werror -ansi -pedantic -I./"
DEBUG='-g -g3 -ggdb -ggdb3'

$COMPILER main.c eval_expr.c $FLAGS $DEBUG -o eval_expr
$COMPILER test.c eval_expr.c $FLAGS $DEBUG -o test
