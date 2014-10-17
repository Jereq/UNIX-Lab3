#!/bin/sh

calcSourceFilename=$(basename "$1")
origExtension="${calcSourceFilename##*.}"
origName="${calcSourceFilename%.*}"

cSourceFilename="${origName}.c"

tempSourceFilename=$(tempfile)
trap 'rm "$tempSourceFilename"' 0 1 2 3 15

./calc3c <$1 >"$tempSourceFilename"
cat prologue.c "$tempSourceFilename" epilogue.c >"$cSourceFilename"
gcc -g "$cSourceFilename" -lm -o "$origName"
