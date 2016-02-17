#!/bin/bash

if [ ! -d "GeneratorGraphs" ]; then
    mkdir ./GeneratorGraphs
fi

for zod in $(seq 1 500)
do
    `python generator.py 40 1200 > GeneratorGraphs/infile${zod}`
done
