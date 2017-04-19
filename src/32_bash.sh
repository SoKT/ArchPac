#!/bin/bash

pacman -Qq > $PWD/2var/Packages.dat
pacman -Qi | grep "Required By     : "  | cut -c19- > $PWD/2var/Required.dat


Pac="2var/Packages.dat"
PaI="$PWD/2var"
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
cat $PWD/$FILE | sed "s/$M2.*/$M2$(cat $PWD/2var/$MW.dat)\;/g" > $PWD/$FILE\.copy
cat $PWD/$FILE\.copy > $PWD/$FILE
M2=$M$DW\=
cat $PWD/$FILE | sed "s/$M2.*/$M2$(cat $PWD/2var/$DW.dat)\;/g" > $PWD/$FILE\.copy
cat $PWD/$FILE\.copy > $PWD/$FILE
M2=$M$PC\=
cat $PWD/$FILE | sed "s/$M2.*/$M2$(cat $PWD/2var/$PC.dat)\;/g" > $PWD/$FILE\.copy
cat $PWD/$FILE\.copy > $PWD/$FILE

rm $PWD/$FILE\.copy
