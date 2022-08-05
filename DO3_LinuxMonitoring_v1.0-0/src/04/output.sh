#!/bin/bash

echo -en ${VALNAME}${BGVALNAME}HOSTNAME; tput sgr0
echo -e ' =' ${VAL}${BGVAL}$(hostname); tput sgr0
echo -en ${VALNAME}${BGVALNAME}TIMEZONE; tput sgr0
echo $(timedatectl) | awk -v color="$VAL$BGVAL" -v reset="$(tput sgr0)" '{printf(" = %s %s %s %s%s \n",color,$20,$12,$6,reset)}' 
echo -en ${VALNAME}${BGVALNAME}USER; tput sgr0
echo -e ' =' ${VAL}${BGVAL}$(whoami); tput sgr0
echo -en ${VALNAME}${BGVALNAME}OS; tput sgr0
echo $(cat /etc/issue) | awk -v color="$VAL$BGVAL" -v reset="$(tput sgr0)" '{printf(" = %s%s %s %s%s\n",color,$1,$2,$3,reset)}'
echo -en ${VALNAME}${BGVALNAME}DATE; tput sgr0
echo $(date) | awk -v color="$VAL$BGVAL" -v reset="$(tput sgr0)" '{printf(" = %s%s %s %s %s%s\n",color,$2,3,$4,$5,reset)}'
echo -en ${VALNAME}${BGVALNAME}UPTIME; tput sgr0
echo -e ' =' ${VAL}${BGVAL}$(uptime -p); tput sgr0
echo -en ${VALNAME}${BGVALNAME}UPTIME_SEC; tput sgr0
echo $(cat /proc/uptime) | awk -v color="$VAL$BGVAL" -v reset="$(tput sgr0)" -v sec=" sec" '{printf(" = %s%s%s\n",color,$2,sec,reset)}'
echo -en ${VALNAME}${BGVALNAME}IP; tput sgr0
echo -e ' =' ${VAL}${BGVAL}$(hostname -I); tput sgr0
echo -en ${VALNAME}${BGVALNAME}MASK; tput sgr0
echo $(netstat -rn) | awk -v color="$VAL$BGVAL" -v reset="$(tput sgr0)" '{printf(" = %s%s%s\n",color,$23,reset)}'
echo -en ${VALNAME}${BGVALNAME}GATEWAY; tput sgr0
echo $(ip r show) | awk -v color="$VAL$BGVAL" -v reset="$(tput sgr0)" '{printf(" = %s%s%s\n",color,$3,reset)}'
echo -en ${VALNAME}${BGVALNAME}RAM_TOTAL; tput sgr0
echo Gb $(free) | awk -v color="$VAL$BGVAL" -v reset="$(tput sgr0)" '{printf(" = %s %.3f %s%s\n",color,$9/1048576, $1, reset)}'
echo -en ${VALNAME}${BGVALNAME}RAM_USED; tput sgr0
echo Gb $(free) | awk -v color="$VAL$BGVAL" -v reset="$(tput sgr0)" '{printf(" = %s %.3f %s%s\n",color,$10/1048576, $1, reset)}'
echo -en ${VALNAME}${BGVALNAME}RAM_FREE; tput sgr0
echo Gb $(free) | awk -v color="$VAL$BGVAL" -v reset="$(tput sgr0)" '{printf(" = %s %.3f %s%s\n",color,$11/1048576, $1, reset)}'
echo -en ${VALNAME}${BGVALNAME}SPACE_ROOT; tput sgr0
echo MB $(df /) | awk -v color="$VAL$BGVAL" -v reset="$(tput sgr0)" '{printf(" = %s %.2f %s%s\n",color,$10/1024, $1, reset)}'
echo -en ${VALNAME}${BGVALNAME}SPACE_ROOT_USED; tput sgr0
echo MB $(df /) | awk -v color="$VAL$BGVAL" -v reset="$(tput sgr0)" '{printf(" = %s %.2f %s%s\n",color,$11/1024, $1, reset)}'
echo -en ${VALNAME}${BGVALNAME}SPACE_ROOT_FREE; tput sgr0
echo MB $(df /) | awk -v color="$VAL$BGVAL" -v reset="$(tput sgr0)" '{printf(" = %s %.2f %s%s\n",color,$12/1024, $1, reset)}'
echo "   "
if [ $deflt -eq 0 ]; then
echo Column 1 background = $bg1 "("$TXTBGVALNAME")"
echo Column 1 font color = $txt1 "("$TXTVALNAME")"
echo Column 2 background = $bg2 "("$TXTBGVAL")"
echo Column 2 font color = $txt2 "("$TXTVAL")"
else 
echo Column 1 background = default "("$TXTBGVALNAME")"
echo Column 1 font color = default "("$TXTVALNAME")"
echo Column 2 background = default "("$TXTBGVAL")"
echo Column 2 font color = default "("$TXTVAL")"
fi

