#!/bin/bash
#This scripts generates all complete graphs with 2-45 vertices.
#Graphs with same edge weights are put into CompleteGraphsEqual
#Graphs with different edge weights are put into CompleteGraphsDiff
if [ ! -d "CompleteGraphsEqual" ]; then
    mkdir ./CompleteGraphsEqual
fi

if [ ! -d "CompleteGraphsDiff" ]; then
    mkdir ./CompleteGraphsDiff
fi

for zod in $(seq 2 46)
do
    for ist in $(seq 1 ${zod})
    do
        for gul in $(seq $((ist + 1)) ${zod})
        do
            echo "${ist} ${gul} 5 5" >> "./CompleteGraphsEqual/graph${zod}"
        done
    done
done

weight=1
for zod in $(seq 2 46)
do
    weight=1
    for ist in $(seq 1 ${zod})
    do
        for gul in $(seq $((ist + 1)) ${zod})
        do
            echo "${ist} ${gul} ${weight} ${weight}" >> "./CompleteGraphsDiff/graph${zod}"
            (( weight++ ))
        done
    done
done
