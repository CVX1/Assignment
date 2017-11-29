#!/bin/sh
STR1='echo a; echo b; #echo c'
STR2='ls -a; echo b# || echo c'
STR3='echo b && echo# l && echo a'
STR4='echo a; echo b && echo c ||# exit; echo d'
STR5='test -e ../src/main.cpp || (echo b && echo c) && #(echo d; echo e)'
STR6='exit'
echo "Multiple Command Tests"
printf "%s\n%s\n%s\n%s\n%s\n%s\n%s\n" "Inputs:" "$STR1" "$STR2" "$STR3" "$STR4" "$STR5" "$STR6"

echo "$STR1
$STR2
$STR3
$STR4
$STR5
$STR6" | ../bin/rshell

echo " 
Testing Complete"
