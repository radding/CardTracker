#!/bin/bash

FILES1=./trainingSet/negativeSubsets/1-4200/*.JPG
FILES2=./trainingSet/negativeSubsets/4201-8400/*.JPG
FILES3=./trainingSet/negativeSubsets/8401-12600/*.JPG
FILES4=./trainingSet/negativeSubsets/12601-16800/*.JPG
FILES5=./trainingSet/negativeSubsets/16801-21000/*.JPG
FILES6=./trainingSet/negativeSubsets/21001-25200/*.JPG
FILES7=./trainingSet/negativeSubsets/25201-29400/*.JPG
FILES8=./trainingSet/negativeSubsets/29401-33600/*.JPG
FILES9=./trainingSet/negativeSubsets/33601-37800/*.JPG
FILES10=./trainingSet/negativeSubsets/37801-42000/*.JPG
FILES11=./trainingSet/negativeSubsets/42001-46200/*.JPG
FILES12=./trainingSet/negativeSubsets/46201-50400/*.JPG
FILES13=./trainingSet/negativeSubsets/50401-54600/*.JPG
FILES14=./trainingSet/negativeSubsets/54601-58997/*.JPG

FILES15=./trainingSet/positiveSubsets/1-850/*.JPG
FILES16=./trainingSet/positiveSubsets/851-1700/*.JPG
FILES17=./trainingSet/positiveSubsets/1701-2550/*.JPG
FILES18=./trainingSet/positiveSubsets/2551-3400/*.JPG
FILES19=./trainingSet/positiveSubsets/3401-4250/*.JPG
FILES20=./trainingSet/positiveSubsets/4251-5100/*.JPG
FILES21=./trainingSet/positiveSubsets/5101-5950/*.JPG
FILES22=./trainingSet/positiveSubsets/5951-6800/*.JPG
FILES23=./trainingSet/positiveSubsets/6801-7650/*.JPG
FILES24=./trainingSet/positiveSubsets/7651-8500/*.JPG
FILES25=./trainingSet/positiveSubsets/8501-9350/*.JPG
FILES26=./trainingSet/positiveSubsets/9351-10200/*.JPG
FILES27=./trainingSet/positiveSubsets/10201-11050/*.JPG
FILES28=./trainingSet/positiveSubsets/11051-11405/*.JPG



i=0
for f in $FILES1
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/1-4200/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES2
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/4201-8400/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES3
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/8401-12600/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES4
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/12601-16800/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES5
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/16801-21000/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES6
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/21001-25200/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES7
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/25201-29400/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES8
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/29401-33600/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES9
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/33601-37800/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES10
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/37801-42000/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES11
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/42001-46200/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES12
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/46201-50400/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES13
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/50401-54600/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES14
do
    echo "Processing $f file..."
    mv $f ./trainingSet/negativeSubsets/54601-58997/$i.JPG
    i=`expr $i + 1`
done





i=0
for f in $FILES15
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/1-850/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES16
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/851-1700/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES17
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/1701-2550/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES18
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/2551-3400/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES19
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/3401-4250/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES20
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/4251-5100/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES21
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/5101-5950/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES22
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/5951-6800/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES23
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/6801-7650/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES24
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/7651-8500/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES25
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/8501-9350/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES26
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/9351-10200/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES27
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/10201-11050/$i.JPG
    i=`expr $i + 1`
done

i=0
for f in $FILES28
do
    echo "Processing $f file..."
    mv $f ./trainingSet/positiveSubsets/11051-11405/$i.JPG
    i=`expr $i + 1`
done

