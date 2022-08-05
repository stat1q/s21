#!/bin/bash
sudo chmod +x mask.sh

start_date=$(date)
start_sec=$(date +%s)

if [ $# -eq 0 ]
then
    echo "Invalid input: Enter 1 parameters (1, 2 or 3)"
else
if [[ !($1 =~ ^[1-3]$) ]]; then
    echo "Invalid input: Parameter must be a number from 1 to 3: $1"
    echo "          1. Clear by log file."
    echo "          2. Clear by creation date and time."
    echo "          3. By name mask (i.e. characters, underlining and date."
else
if [[ $1 -eq 1 ]]; then
    if [[ $# -ge 2 && -f $2 && $2 =~ .+[\.log]$ ]]; then
        flog=$2
    else
        flog="../02/generator.log"
    fi
    sort $flog | grep -e "file\|folder" | awk '{system("rm -df "$3)}'
elif [[ $1 -eq 2 ]]; then
    read -p "Enter start time up to a minute (example: 10:20): " start
    read -p "Enter end time up to a minute (example: 10:25 , i.e. running time is 4 minutes): " end
    find / -newermt "$start" ! -newermt "$end" 2>/dev/null | sort -r | awk '{system("rm -df "$1" 2>/dev/null")}'
elif [[ $1 -eq 3 ]]; then
    source ./mask.sh
    read -p "Enter a mask for a file name (letters, an underscore and a date. Example: abc_060422): " msk
    if [[ $msk =~ ^[a-zA-Z]+_([0-9]{6})$ ]]; then
        mask=$(domask $msk)
        find / -regex "$mask" 2>/dev/null | awk '{system("rm -df "$1" 2>/dev/null")}'
    else
        echo "The mask does not match the pattern (mask example: abcd_070422)."
        echo "Try again..."
    fi
    read -p "Enter a mask for a folder name (letters, an underscore and a date. Example: abc_060422): " msk
    if [[ $msk =~ ^[a-zA-Z]+_([0-9]{6})$ ]]; then
        mask=$(domask $msk)
        find / -regex "$mask" 2>/dev/null | awk '{system("rm -df "$1" 2>/dev/null")}'
    else
        echo "The mask does not match the pattern (mask example: abcd_070422)."
        echo "Try again..."
    fi; fi; fi; fi
    
end_date=$(date)
end_sec=$(date +%s)
work_sec=$(($end_sec - $start_sec))
echo 
echo work start  - $start_date
echo work end    - $end_date
echo $work_sec seconds
