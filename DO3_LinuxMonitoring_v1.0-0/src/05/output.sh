#!/bin/bash
source var.conf 
# Вывод общего количества папок
folderNum=$( sudo ls -laR $1 | grep ^d | wc -l )
echo Total number of folders '('including all nested ones')' = $folderNum

# Топ 5 папок с самым юольшим весом
folderInfo=$( sudo du -h $1 | sort -rh | head -6 )
checkFolderNum=$( sudo du -h $1 | wc -l  )

echo TOP 5 folders of maximum size arranged in descending order '('path and size')':
if [ $checkFolderNum -le 1 ]; then
echo No subfolders
else
for (( i = 1; i <= 5; i++ )); do
varS=$( echo $folderInfo | awk -v S=$countS '{printf("%s", $S)}' )
varP=$( echo $folderInfo | awk -v P=$countP '{printf("%s", $P)}' )
echo $i - $varP/, $varS
countS=$(( $countS + 2 ))
countP=$(( $countP + 2 )); done; fi

# Вывод общего количества файлов
fileNum=$( sudo ls -laR $1 | grep ^- | wc -l )
#fileNum2=$( sudo find $path -type f | wc -l )
echo Total number of files = $fileNum

# Кол-во файлов по типам
echo Nunber of:
# Кол-во conf файлов
confNum=$( sudo find $1 -name '*.conf' | wc -l )
echo Configuration files '('with the .conf extension')' = $confNum
# Кол-во txt файлов
txtNum=$( sudo find $1 -name '*.txt' | wc -l )
echo Text files = $txtNum
# Кол-во исполняемых файлов
exFileNum=$( sudo find $1 -type f -executable | wc -l )
echo Executable files = $exFileNum
# Кол-во log файлов
logNum=$( sudo find $1 -name '*.log' | wc -l )
echo Log files '('with the extension .log')' = $logNum
# Кол-во архивных файлов
arcNum=$( sudo find $1 -name '*.tar' -o -name '*.zip' -o -name '*.7z' -o -name '*.rar' -o -name '*.gz' | wc -l )
echo Archive files = $arcNum
# Кол-во символических ссылок
linkNum=$( sudo find $1 -type l | wc -l )
echo Symbolic links =  $linkNum

# Топ 10 файлов по размеру 
echo TOP 10 files of maximum size arranged in descending order '('path, size and type')':
fileInfo=$( sudo find $1 -type f | sudo xargs -d '\n' du -ha | sort -rh | head -10 )
checkFileNum=$( sudo find $1 -type f | wc -l )

if [ $checkFileNum -eq 0 ]; then
echo No files in this folder
else
for (( a = 1; a <= 10; a++ )); do
varFileS=$( echo $fileInfo | awk -v S=$countFileS '{printf("%s", $S)}' )
varFileP=$( echo $fileInfo | awk -v P=$countFileP '{printf("%s", $P)}' )
FileType=$( find $varFileP -name '*.*' | wc -l )
if [ $FileType -eq 1 ]; then
varFileT=$( echo $varFileP | awk -F. '{print $(NF)}' )
elif [ $FileType -eq 0 ]; then
varFileT='---'; fi
echo $a - $varFileP, $varFileS, $varFileT
countFileS=$(( $countFileS + 2 ))
countFileP=$(( $countFileP + 2 )); done; fi

# Топ 10 исполняемых файлов по размеру
echo TOP 10 executable files of the maximum size arranged in descending order '('path, size and MD5 hash of file')':
exFileInfo=$( sudo find $1 -type f -executable | sudo xargs -r -d '\n' du -h | sort -rn | head -10 )
checkExNum=$( sudo find $1 -type f -executable | wc -l )

if [ $checkExNum -eq 0 ]; then
echo No executable files
else
for (( b = 1; b <= 10; b++ )); do
varExFileS=$( echo $exFileInfo | awk -v S=$countExFileS '{printf("%s", $S)}' )
varExFileP=$( echo $exFileInfo | awk -v P=$countExFileP '{printf("%s", $P)}' )
md5=$( md5sum $varExFileP | awk '{print $1}' )
echo $b - $varExFileP, $varExFileS, $md5 
countExFileS=$(( $countExFileS + 2 ))
countExFileP=$(( $countExFileP + 2 )); done; fi

# Время выполнения скрипта
echo Script execution time '('in seconds')' = $SECONDS








