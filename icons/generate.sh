#!/bin/bash

app="harbour-sailhub"

sizes=(86 108 128 172)

# optimze svg
scour $app.svg $app-optimized.svg

# copy optimized svg to scaleable folder
cp $app-optimized.svg scaleable/$app.svg
rm $app-optimized.svg

# convert to png
for size in "${sizes[@]}";
do
inkscape --export-overwrite -C -o $size"x"$size/$app.png -w $size -h $size $app.svg
optipng $size"x"$size/$app.png
done
