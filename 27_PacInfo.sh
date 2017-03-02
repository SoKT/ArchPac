Pac="var/Packages.dat"
#PaI="$PWD/PacInfo.log"
PaI="$PWD/var"
#echo Line Count > $PaI
cat $Pac | wc -l > $PaI/PacCount.dat
#echo Longest Line  >> $PaI
cat $Pac | wc -L > $PaI/MaxWidth.dat

cat $PaI/Required.dat | wc -L > $PaI/DepWidth.dat
