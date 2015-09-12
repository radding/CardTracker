#!/bin/bash
FILES=./data/*.jpg
FILES1=./data/*.JPG
FILES2=./data/*.m4v

for f in $FILES
do
    echo "Processing $f..."
    # take action on each file. $f store current file name
    ./main 0 $f
done

for f in $FILES1
do
    echo "Processing $f..."
    # take action on each file. $f store current file name
    ./main 0 $f
done

for f in $FILES2
do
    echo "Processing $f..."
    # take action on each file. $f store current file name
    ./main 1 $f
done
