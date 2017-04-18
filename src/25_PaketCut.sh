#!/bin/bash
#$HOME/code/04_18_2017/src/25_PaketCut.sh


pacman -Qq > $PWD/2var/var/Packages.dat
pacman -Qi | grep "Required By     : "  | cut -c19- > $PWD/2var/var/Required.dat
#rm $PWD/2var/var/RepoName.dat
#for i in $(pacman -Qq); do pacman -Ss ^$i$; done >> $PWD/2var/var/RepoName.dat
#^_This command can take long time_^
cat $PWD/2var/var/RepoName.dat | sed 'n;d' > $PWD/2var/var/RepoName2.dat
cat $PWD/2var/var/RepoName2.dat | grep "installed" > $PWD/2var/var/RepoName3.dat
cat $PWD/2var/var/RepoName3.dat | cut -d"/" -f1 > $PWD/2var/var/RepoName4.dat
cat $PWD/2var/var/RepoName3.dat | cut -d" " -f1 | cut -d"/" -f2 > $PWD/2var/var/RepoName5.dat
pacman -Sl | grep "installed" > $PWD/2var/var/RepoName6.dat
