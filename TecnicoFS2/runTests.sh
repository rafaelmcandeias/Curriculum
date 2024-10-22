#!/usr/bin/env zsh

inputdir=$1
outputdir=$2
maxthreads=$3
n=1

for inputfile in $inputdir/*.txt
do
    while (( $n <= $maxthreads ))
    do
        echo InputFile=$inputfile NumThreads=$n
        ./tecnicofs $inputfile $outputdir/$(basename $inputfile .txt) $n | grep "TecnicoFS"
        n=$(( n+1 ))
    done
    n=1
done
