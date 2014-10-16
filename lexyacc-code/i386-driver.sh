#!/bin/sh

./calc3i <$1 >tmp.s
cat prologue.s tmp.s epilogue.s >tmp2.s
as -gstabs tmp2.s -o tmp.o
gcc -lc -o a.out tmp.o
