#!/bin/bash
# Switch file path between negative and positive
# to rename all files in each directory
# FILES=./trainingSet/negative/*.JPG
# FILES=./trainingSet/positive/*.JPG

FILES=./trainingSet/negative/*.jpg
FILES1=./trainingSet/negative/*.JPG
i=0
for f in $FILES
do
    echo "Processing $f file..."
    # take action on each file. $f store current file name
    mv $f ./trainingSet/negative/$i.JPG
    i=`expr $i + 1`
done

for f in $FILES1
do
    echo "Processing $f file..."
    # take action on each file. $f store current file name
    mv $f ./trainingSet/negative/$i.jpg
    i=`expr $i + 1`
done