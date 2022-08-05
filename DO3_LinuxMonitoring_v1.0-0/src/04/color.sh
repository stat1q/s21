#!/bin/bash
source var.conf
clear

for (( a = 0; a <= 3; a++ )); do
clrarr[a]=$(awk -F= 'NR=='$count' {print $2}' conf)
count=$(( $count + 1 )); done

for clr in "${clrarr[@]}"; do
if (echo "$clr" | grep -E -q -v -e "^1$" -e "^2$" -e "^3$" -e "^4$" -e "^5$" -e "^6$"); then
clrarr=(${defarr[@]}); def=1; break; fi; done

if [ ${clrarr[0]} -eq ${clrarr[1]} ] || [ ${clrarr[2]} -eq ${clrarr[3]} ]; then
def=1; clrarr=(${defarr[@]}); fi

export deflt=$def
export bg1=${clrarr[0]}; export bg2=${clrarr[2]}; export txt1=${clrarr[1]}; export txt2=${clrarr[3]}

if [ $bg1 -eq 1 ]; then
export BGVALNAME=$BGWHITE; export TXTBGVALNAME="white"
elif [ $bg1 -eq 2 ]; then
export BGVALNAME=$BGRED; export TXTBGVALNAME="red"
elif [ $bg1 -eq 3 ]; then
export BGVALNAME=$BGGREEN; export TXTBGVALNAME="green"
elif [ $bg1 -eq 4 ]; then
export BGVALNAME=$BGBLUE; export TXTBGVALNAME="blue"
elif [ $bg1 -eq 5 ]; then
export BGVALNAME=$BGPURPLE; export TXTBGVALNAME="purple"
elif [ $bg1 -eq 6 ]; then
export BGVALNAME=$BGBLACK; export TXTBGVALNAME="black"; fi

if [ $txt1 -eq 1 ]; then
export VALNAME=$WHITE; export TXTVALNAME="white"
elif [ $txt1 -eq 2 ]; then
export VALNAME=$RED; export TXTVALNAME="red"
elif [ $txt1 -eq 3 ]; then
export VALNAME=$GREEN; export TXTVALNAME="green"
elif [ $txt1 -eq 4 ]; then
export VALNAME=$BLUE; export TXTVALNAME="blue"
elif [ $txt1 -eq 5 ]; then
export VALNAME=$PURPLE; export TXTVALNAME="purple"
elif [ $txt1 -eq 6 ]; then
export VALNAME=$BLACK; export TXTVALNAME="black"; fi

if [ $bg2 -eq 1 ]; then
export BGVAL=$BGWHITE; export TXTBGVAL="white"
elif [ $bg2 -eq 2 ]; then
export BGVAL=$BGRED; export TXTBGVAL="red"
elif [ $bg2 -eq 3 ]; then
export BGVAL=$BGGREEN; export TXTBGVAL="green"
elif [ $bg2 -eq 4 ]; then
export BGVAL=$BGBLUE; export TXTBGVAL="blue"
elif [ $bg2 -eq 5 ]; then
export BGVAL=$BGPURPLE; export TXTBGVAL="purple"
elif [ $bg2 -eq 6 ]; then
export BGVAL=$BGBLACK; export TXTBGVAL="black"; fi

if [ $txt2 -eq 1 ]; then
export VAL=$WHITE; export TXTVAL="white"
elif [ $txt2 -eq 2 ]; then
export VAL=$RED; export TXTVAL="red"
elif [ $txt2 -eq 3 ]; then
export VAL=$GREEN; export TXTVAL="green"
elif [ $txt2 -eq 4 ]; then
export VAL=$BLUE; export TXTVAL="blue"
elif [ $txt2 -eq 5 ]; then
export VAL=$PURPLE; export TXTVAL="purple"
elif [ $txt2 -eq 6 ]; then
export VAL=$BLACK; export TXTVAL="black"; fi

bash output.sh
