#!/bin/bash
sudo chmod +x folder.sh file.sh
start_date=$(date)
start_sec=$(date +%s)

if [ $# -ne 3 ]; then
    echo "Invalid input: Enter 3 parameters"
else
if [[ $(echo $1 | wc -c) -gt 8 ]]; then
    echo "Invalid input: Parameter 1 (folder name letter list) must be no more than 7 characters: $1"
else
if [[ !($1 =~ ^([a-zA-Z]+)$) ]]; then
    echo "Invalid input: Parameter 1 (folder name letter list) must be only from the English alphabet: $1"
else
if [[ !($2 =~ ^[a-zA-Z]+\.[a-zA-Z]+$ ) ]]; then
    echo "Invalid input: Parameter 2 (file name letter list) must be only from the English alphabet $2"
else
filename=$(echo $2 | cut -d. -f1)
if [[ $(echo $filename | wc -c) -gt 8 ]]; then
    echo "Invalid input: Parameter 2 (file name letter list) must be no more than 7 characters before the dot: $filename"
else
if [[ !($filename =~ ^([a-zA-Z]+)$) ]]; then
    echo "Invalid input: Parameter 2 (file name letter list) must be only from the English alphabet: $filename"
else
filext=$(echo $2 | cut -d. -f2)
if [[ $(echo $filext | wc -c) -gt 4 ]]; then
    echo "Invalid input: Parameter 2 (file name letter list) must be no more than 3 characters after the dot: $filext"
else
if [[ !($filext =~ ^([a-zA-Z]+)$) ]]; then
    echo "Invalid input: Parameter 2 (file name letter list) must be only from the English alphabet: $filext"
else
if [[ !($3 =~ ^[0-9]+(MB)$) ]]; then
    echo "Invalid input: Parametr 3 (file size) must be in Megabytes (MB): $3"
else
filesize=$(echo $3 | sed 's/MB//')
if [ $filesize -gt 100 ]; then
    echo "Invalid input: Parametr 3 (file size) must be no more 100MB: $3"
else
find / -type d 2>/dev/null | grep -v -e "bin" -e"dev" > list
alldir=$(cat list | wc -l)
alldir=$(($alldir % 32767))
p2=10; p4=10; slash=\/
while [[ $? -eq 0 && $alldir -gt 0 ]]
do
    numdir=$((($RANDOM % $alldir) + 1))
    p1=$(cat list | head -n$numdir | tail -n1)
    sed -i "${numdir}d" list
    alldir=$(($alldir - 1))
    ./folder.sh $1 $p2 $p1$slash $filename $p4 $filext $(($filesize * 1024 * 1024)) $3
done; fi; fi; fi; fi; fi; fi; fi; fi; fi; fi

end_date=$(date)
end_sec=$(date +%s)
work_sec=$(($end_sec - $start_sec))
echo work start  - $start_date | tee -a generator.log
echo work end    - $end_date | tee -a generator.log
echo $work_sec seconds | tee -a generator.log
echo 
