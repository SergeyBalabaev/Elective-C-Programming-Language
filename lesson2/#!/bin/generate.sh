#!/bin/bash
x=1 
a=1
b=1
c=1
folder_up=$(($1+1))
folder=$(($2+1))
files=$(($3+1))
lines=$(($4+1))
mkdir "Files"
cd "Files"
while [ $c -lt $folder_up ] 
do
mkdir "Folder_"$c
cd "Folder_"$c
while [ $x -lt $folder ] 
do
mkdir "Folder_"$x
cd "Folder_"$x
while [ $a -lt $files ]
do 
touch "file_"$a".doc"
while [ $b -lt $lines ] 
do
echo "Password_"$c"_"$x"_"$a"_"$b": "$RANDOM >> "file_"$a".doc"
b=$(($b + 1 ))
done
b=1
a=$(($a + 1 ))
done
a=1
cd ..
x=$(($x + 1 ))
done
x=1
cd ..
c=$(($c + 1 ))
done

a=$(($RANDOM%folder_up))
b=$(($RANDOM%folder))
c=$(($RANDOM%files))
cd "Folder_"$a
cd "Folder_"$b
echo "Password_car: "$RANDOM >> "file_"$c".doc"
