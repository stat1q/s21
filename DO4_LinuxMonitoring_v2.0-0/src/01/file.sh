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

made=0; need=$2; pathdir=$3
filext=$4; kb=$5; kbstr=$6

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
    filename=$pathdir$tmp$(date +_%d%m%y)\.$filext    
    fallocate -l $kb $filename
    echo file created $filename $(date) $kbstr >> ./generator.log
    made=$(($made + 1))
    dfree=$(echo "$(df | grep -e "/$" | awk '{print $4}') / 1024 /1024" | bc -l)
    if [[ $(echo "$dfree < 1" | bc) -eq 1 ]]
    then
        echo little space $pathdir $(date) $dfree"GB" >> ./generator.log
        exit 1
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
                step $next $2; fi; fi; fi
}

if [[ $all -lt 4 ]]; then
    delta=$((4 - $all))
else
    delta=0; fi
while [[ $made -lt $need ]]
do
    step 0 $delta
    delta=$(($delta + 1))
done    
