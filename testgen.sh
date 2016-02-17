#!/bin/bash
for i in `seq 1 100`;
do
    j=$((4*$i));
    python generator.py $i $j > "tests/$i";
done
