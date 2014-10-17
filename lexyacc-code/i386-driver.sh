#!/bin/sh

calcSourceFilename=$(basename "$1")
origExtension="${calcSourceFilename##*.}"
origName="${calcSourceFilename%.*}"

asmSourceFilename="${origName}.s"

tempSourceFilename=$(tempfile)
tempObjectFilename=$(tempfile)
trap 'rm "$tempSourceFilename" "$tempObjectFilename"' 0 1 2 3 15

./calc3i <$1 >"$tempSourceFilename"
cat prologue.s "$tempSourceFilename" epilogue.s >"$asmSourceFilename"
as -gstabs "$asmSourceFilename" -o "$tempObjectFilename"
gcc -lc -o "$origName" "$tempObjectFilename"
