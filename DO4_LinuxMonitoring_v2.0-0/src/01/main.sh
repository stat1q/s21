#!/bin/bash

if [ $# -ne 6 ]; then
    echo "Invalid input: Enter 6 parameters"
else
if [[ ! ( -d $1) ]]; then
    echo "Error: Parameter 1 - No such directory: $1"
else
if [[ !($1 =~ ^\/.*) ]]; then
    echo "Invalid input: Parameter 1 (path) must be absolute: $1"
else
if [[ !($1 =~ .*\/$) ]]; then
    slash=\/; fi
if [[ !($2 =~ ^([0-9]+)$) ]]; then
    echo "Invalid input: Parameter 2 (number of subfolders) must be a number: $2"
else
if [[ $(echo $3 | wc -c) -gt 8 ]]; then
    echo "Invalid input: Parameter 3 (folder name letter list) must be no more than 7 characters: $3"
else
if [[ !($3 =~ ^([a-zA-Z]+)$) ]]; then
    echo "Invalid input: Parameter 3 (folder name letter list) must be only from the English alphabet: $3"
else
if [[ !($4 =~ ^([0-9]+)$) ]]; then
    echo "Invalid input: Parameter 4 (number of files) must be a number: $4"
else
if [[ !($5 =~ ^[a-zA-Z]+\.[a-zA-Z]+$ ) ]]; then
    echo "Invalid input: Parameter 5 (file name letter list) must be only from the English alphabet $5"
else
filename=$(echo $5 | cut -d. -f1)
if [[ $(echo $filename | wc -c) -gt 8 ]]; then
    echo "Invalid input: Parameter 5 (file name letter list) must be no more than 7 characters before the dot: $filename"
else
if [[ !($filename =~ ^([a-zA-Z]+)$) ]]; then
    echo "Invalid input: Parameter 5 (file name letter list) must be only from the English alphabet: $filename"
else
filext=$(echo $5 | cut -d. -f2)
if [[ $(echo $filext | wc -c) -gt 4 ]]; then
    echo "Invalid input: Parameter 5 (file name letter list) must be no more than 3 characters after the dot: $filext"
else
if [[ !($filext =~ ^([a-zA-Z]+)$) ]]; then
    echo "Invalid input: Parameter 5 (file name letter list) must be only from the English alphabet: $filext"
else
if [[ !($6 =~ ^[0-9]+(kb)$) ]]; then
    echo "Invalid input: Parametr 6 (file size) must be in kilobates (kb): $6"
else
filesize=$(echo $6 | sed 's/kb//')
if [ $filesize -gt 100 ]; then
    echo "Invalid input: Parametr 6 (file size) must be no more 100kb: $6"
else
./folder.sh $3 $2 $1$slash $filename $4 $filext $(($filesize * 1024)) $6
fi; fi; fi; fi; fi; fi; fi; fi; fi; fi; fi; fi; fi; fi
