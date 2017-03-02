DW="DepWidth"
ML="MaxLevel"
PC="PacCount"
MW="MaxWidth"
M="const int "
FILE="pac.cpp"

cat $PWD/$FILE > $PWD/$FILE\.backup
#for i 1 to 3
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