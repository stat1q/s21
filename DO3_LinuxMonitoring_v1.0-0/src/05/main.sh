#!/bin/bash

if [ $# != 1 ]; then
echo "Invalid input: 1 parameter"
exit 1
fi

if [ -d "$1" ]; then
path=$( echo $1 | awk '/\/$/{print $1}' )
if [ -z $path ]; then
echo "Path error: Enter path format /folder name/"
exit 1
else
bash output.sh $path 
fi
else 
echo Folder '"'$1'"' not exist 
fi

