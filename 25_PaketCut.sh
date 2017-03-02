pacman -Qq > $PWD/var/Packages.dat
pacman -Qi | grep "Required By     : "  | cut -c19- > $PWD/var/Required.dat
#rm $PWD/var/RepoName.dat
#for i in $(pacman -Qq); do pacman -Ss ^$i$; done >> $PWD/var/RepoName.dat
#^_This command can take long time_^
cat $PWD/var/RepoName.dat | sed 'n;d' > $PWD/var/RepoName2.dat
cat $PWD/var/RepoName2.dat | grep "installed" > $PWD/var/RepoName3.dat
cat $PWD/var/RepoName3.dat | cut -d"/" -f1 > $PWD/var/RepoName4.dat
cat $PWD/var/RepoName3.dat | cut -d" " -f1 | cut -d"/" -f2 > $PWD/var/RepoName5.dat
pacman -Sl | grep "installed" > $PWD/var/RepoName6.dat
