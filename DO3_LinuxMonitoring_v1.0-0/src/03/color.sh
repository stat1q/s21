#!/bin/bash
source var.conf

if [ $1 -eq $2 ]; then
echo "Color mathes background: choose different colors"; match=1
exit 1
elif [ $1 -eq 1 ]; then
export BGVALNAME=$BGWHITE
elif [ $1 -eq 2 ]; then
export BGVALNAME=$BGRED
elif [ $1 -eq 3 ]; then
export BGVALNAME=$BGGREEN
elif [ $1 -eq 4 ]; then
export BGVALNAME=$BGBLUE
elif [ $1 -eq 5 ]; then
export BGVALNAME=$BGPURPLE
elif [ $1 -eq 6 ]; then
export BGVALNAME=$BGBLACK; fi

if [ $match -eq 1 ]; then
exit 1
elif [ $2 -eq 1 ]; then
export VALNAME=$WHITE
elif [ $2 -eq 2 ]; then
export VALNAME=$RED
elif [ $2 -eq 3 ]; then
export VALNAME=$GREEN
elif [ $2 -eq 4 ]; then
export VALNAME=$BLUE
elif [ $2 -eq 5 ]; then
export VALNAME=$PURPLE
elif [ $2 -eq 6 ]; then
export VALNAME=$BLACK; fi

if [ $3 -eq $4 ]; then
echo "Color mathes background: choose different colors"; match=2
exit 1
elif [ $3 -eq 1 ]; then
export BGVAL=$BGWHITE
elif [ $3 -eq 2 ]; then
export BGVAL=$BGRED
elif [ $3 -eq 3 ]; then
export BGVAL=$BGGREEN
elif [ $3 -eq 4 ]; then
export BGVAL=$BGBLUE
elif [ $3 -eq 5 ]; then
export BGVAL=$BGPURPLE
elif [ $3 -eq 6 ]; then
export BGVAL=$BGBLACK; fi

if [ $match -eq 2 ]; then
exit 1
elif [ $4 -eq 1 ]; then
export VAL=$WHITE
elif [ $4 -eq 2 ]; then
export VAL=$RED
elif [ $4 -eq 3 ]; then
export VAL=$GREEN
elif [ $4 -eq 4 ]; then
export VAL=$BLUE
elif [ $4 -eq 5 ]; then
export VAL=$PURPLE
elif [ $4 -eq 6 ]; then
export VAL=$BLACK; fi

bash output.sh
