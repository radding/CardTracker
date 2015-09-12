#!/bin/bash
FILES=./data/*.jpg
FILES1=./data/*.png

for f in $FILES
do
    #echo "Processing $f file..."
    ./main $f
done

for f in $FILES1
do
    #echo "Processing $f file..."
    ./main $f
done