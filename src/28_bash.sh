#!/bin/bash
#$HOME/code/04_18_2017/src/28_bash.sh


DW="DepWidth"
ML="MaxLevel"
PC="PacCount"
MW="MaxWidth"
M="const int "
FILE="pac.cpp"

#cat $PWD/$FILE > $PWD/$FILE\.backup
#for i 1 to 3
M2=$M$MW\=
cat $PWD/$FILE | sed "s/$M2.*/$M2$(cat $PWD/2var/var/$MW.dat)\;/g" > $PWD/$FILE\.copy
cat $PWD/$FILE\.copy > $PWD/$FILE
M2=$M$DW\=
cat $PWD/$FILE | sed "s/$M2.*/$M2$(cat $PWD/2var/var/$DW.dat)\;/g" > $PWD/$FILE\.copy
cat $PWD/$FILE\.copy > $PWD/$FILE
M2=$M$PC\=
cat $PWD/$FILE | sed "s/$M2.*/$M2$(cat $PWD/2var/var/$PC.dat)\;/g" > $PWD/$FILE\.copy
cat $PWD/$FILE\.copy > $PWD/$FILE

rm $PWD/$FILE\.copy
