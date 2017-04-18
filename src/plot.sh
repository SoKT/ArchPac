#!/bin/bash
echo "Start creating:"
date
ulimit -m 5000
gnuplot << EOP

set size square
set palette rgb 34,35,36
#set xrange [-10:9000]
#set yrange [9000:-10]
set xrange [10:9000]
set yrange [10:9000]
set terminal png size 10100,10100
set output "$PWD/../png/img $(date).png"

################################
# example matrix
# 0 0 0 1 2 2 1 0 0 0
# 0 0 2 3 3 3 3 2 0 0
# 0 2 3 4 4 4 4 3 3 0
# 2 3 4 5 5 5 5 4 3 2
# 3 4 5 6 7 7 6 5 4 3
# 3 4 5 6 7 7 6 5 4 3
# 2 3 4 5 5 5 5 4 3 2
# 0 2 3 4 4 4 4 3 2 0
# 0 0 2 3 3 3 3 2 0 0
# 0 0 0 1 2 2 1 0 0 0

plot '$PWD/../var/Bitmaple.dat' matrix with image

EOP

echo "End of creating:"
date
