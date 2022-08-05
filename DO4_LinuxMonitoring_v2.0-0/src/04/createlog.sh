#!/bin/bash
source ./numgen.sh
source ./codes.sh

records=$(($(numgen 900) + 101)) 
for ((i=0; i<$records; i++))
do
    ttime=$(timegen)
    echo -e "$ttime\t$(ipgen) - [$1:$ttime +0700] \"${method[$(numgen 5)]} /$(numgen1 9)/$(numgen1 15)/$(numgen1 20).html HTTP/1.1\" ${code[$(numgen 10)]} - - \"${agent[$(numgen 8)]}\"" 
done
