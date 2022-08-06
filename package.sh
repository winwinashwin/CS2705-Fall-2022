#!/bin/bash -e

read -p "Assignment : " n_a

dirname=$(printf "Assignment-%02d" $n_a)
packed=$(printf "CS2705_Assignment-%02d_NA19B001" $n_a)
[[ -d $dirname ]] && zip -r $packed $dirname
