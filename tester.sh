#!/bin/bash
for i in `seq 1 100`;
do
        ./refnetplan "tests/$i" > "refnetfile";
        ./netplan "tests/$i" > "netplanfile";
        diff "refnetfile" "netplanfile";
        rm "refnetfile";
        rm "netplanfile";
done
