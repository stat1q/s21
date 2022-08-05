#!/bin/bash

bash output.sh
echo "You want to save file? (Y/N)"
read ans
if [ $ans = "Y" ] || [ $ans = "y" ]
then
file=$(date +%d_%m_%Y_%H_%M_%S).status
bash output.sh >> $file
echo "Saved in $file"
fi
