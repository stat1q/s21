#!/bin/bash
start_date=$(date)
start_sec=$(date +%s)

if [ $# -eq 0 ]; then
   echo "Invalid input: Enter 1 parameters (1, 2, 3 or 4)"
else
if [[ !($1 =~ ^[1-4]$) ]]; then
    echo "Invalid input: Parameter must be a number from 1 to 4: $1"
    echo "          1. All entries sorted by response code."
    echo "          2. All unique IPs found in the entries."
    echo "          3. All requests with errors (response code -4xx or 5xx)."
    echo "          4. All unique IPs found among the erroneous requests."
else
if [[ $1 -eq 1 ]]; then
    sort -t' ' -k 8 ../04/*.log
elif [[ $1 -eq 2 ]]; then
    awk '{print $1}' ../04/*.log | sort -t '.' -k1,1n -k2,2n -k3,3n -k4,4n -u
elif [[ $1 -eq 3 ]]; then
    awk '($8~"4..")||($8~"5.."){print $6}' ../04/*.log
else
    awk '($8~"4..")||($8~"5.."){print $1}' ../04/*.log | sort -t '.' -k1,1n -k2,2n -k3,3n -k4,4n -u
fi; fi; fi

end_date=$(date)
end_sec=$(date +%s)
work_sec=$(($end_sec - $start_sec))
echo 
echo work start  - $start_date
echo work end    - $end_date
echo $work_sec seconds
