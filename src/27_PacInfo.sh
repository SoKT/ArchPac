#!/bin/bash
#$HOME/code/04_18_2017/src/27_PacInfo.sh


Pac="2var/var/Packages.dat"
#Info="$PWD/PacInfo.log"
PaI="$PWD/2var/var"
#echo Line Count > $Info
cat $Pac | wc -l > $PaI/PacCount.dat
#echo Longest Line  >> $Info
cat $Pac | wc -L > $PaI/MaxWidth.dat
#echo Dependencies Width  >> $Info
cat $PaI/Required.dat | wc -L > $PaI/DepWidth.dat
