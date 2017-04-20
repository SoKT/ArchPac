#!/bin/bash

pacman -Qq > $PWD/var/Packages.dat
pacman -Qi | grep "Required By     : "  | cut -c19- > $PWD/var/Required.dat


Pac="var/Packages.dat"
PaI="$PWD/var"
cat $Pac | wc -l > $PaI/PacCount.dat
cat $Pac | wc -L > $PaI/MaxWidth.dat
cat $PaI/Required.dat | wc -L > $PaI/DepWidth.dat


DW="DepWidth"
ML="MaxLevel"
PC="PacCount"
MW="MaxWidth"
M="const int "
FILE="pac.cpp"


M2=$M$MW\=
cat $PWD/$FILE | sed "s/$M2.*/$M2$(cat $PWD/var/$MW.dat)\;/g" > $PWD/$FILE\.copy
cat $PWD/$FILE\.copy > $PWD/$FILE
M2=$M$DW\=
cat $PWD/$FILE | sed "s/$M2.*/$M2$(cat $PWD/var/$DW.dat)\;/g" > $PWD/$FILE\.copy
cat $PWD/$FILE\.copy > $PWD/$FILE
M2=$M$PC\=
cat $PWD/$FILE | sed "s/$M2.*/$M2$(cat $PWD/var/$PC.dat)\;/g" > $PWD/$FILE\.copy
cat $PWD/$FILE\.copy > $PWD/$FILE

rm $PWD/$FILE\.copy
