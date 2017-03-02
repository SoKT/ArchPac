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
#M2=$M$ML\=
#cat $PWD/$FILE | sed "s/$M2.*/$M2$(cat $PWD/var/$ML.dat)\;/g" > $PWD/$FILE\.copy
#cat $PWD/$FILE\.copy > $PWD/$FILE
M2=$M$PC\=
cat $PWD/$FILE | sed "s/$M2.*/$M2$(cat $PWD/var/$PC.dat)\;/g" > $PWD/$FILE\.copy
cat $PWD/$FILE\.copy > $PWD/$FILE
rm $PWD/$FILE\.copy



############################################
#for i=1 to paccount 
#echo 1 >> paclevel

#for i=1 to paccount

#    if dep<>none 

#    for j=1 to CountWords
#    if paclevel>=pacreclevel
#    pacreclevel=paclevel+1

#читаем файл зависимостей построчно
#для каждой строки читаем по словам
#если уровень зависимости выше или равен уровню зависимого
#уровень зависимого = уровень зависимости + 1
