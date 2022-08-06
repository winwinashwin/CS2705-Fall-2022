#!/bin/bash -e

read -p "Assignment Number: " n_a
read -p "Question Number  : " n_q

dirname=$(printf "Assignment-%02d" $n_a)

if [[ ! -d $dirname ]]; then mkdir -p $dirname; fi

filename=$(printf "A%02d_Q%02d_NA19B001.cpp" $n_a $n_q)

pushd $dirname > /dev/null

if [[ -f $filename ]]; then
    echo "$filename already exists!"
else
    sed "s/{{FILENAME}}/$filename/g" ../soln-template.cpp > $filename
fi

popd > /dev/null

nvim $dirname/$filename
