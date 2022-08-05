#!/bin/bash
declare -a char
declare -a num
all=${#1}  
last=$(($all - 1))

for ((i=0; i<$all; i++))
do
    char[i]="${1:$i:1}"
    num[i]=0
done

made=0; need=$(($RANDOM % 100 + 1)); pathdir=$3
filename=$4; countf=$5; filext=$6; kb=$7; kbstr=$8

function create {
    local tmp=""; local i; local j
    for ((i=0; i<$all; i++))
    do
        tmp=$tmp${char[i]}
        for ((j=0; j<${num[i]}; j++))
        do
            tmp=$tmp${char[i]}
        done
    done
    dirname=$pathdir$tmp$(date +_%d%m%y)    
    mkdir $dirname 2>> ./error
    if [[ $? -eq 0 ]]; then
        echo folder created $dirname $(date) >> ./generator.log
        made=$(($made + 1))    
        ./file.sh $filename $countf $dirname"/" $filext $kb $kbstr
        if [[ $? -eq 1 ]]
        then
            exit 1
        fi
    else
        exit 0
    fi
}

function step {
    if [[ $made -lt $need ]]; then
        if [[ $2 -eq 0 ]]; then
            create
        else
            if [[ $1 -eq $last ]]; then
                num[last]=$((${num[last]} + $2))
                create
                num[last]=$((${num[last]} - $2))
            else
                local next=$(($1 + 1)); local i
                for ((i=1; i<=$2 ; i++))
                do
                    num[$1]=$((${num[$1]} + 1))
                    step $next $(($2 - $i))
                done
                num[$1]=0
                step $next $2
                fi; fi; fi
}

if [[ $all -lt 5 ]]; then
    delta=$((5 - $all))
else
    delta=0
fi
while [[ $made -lt $need ]]
do
    step 0 $delta
    delta=$(($delta + 1))
done    