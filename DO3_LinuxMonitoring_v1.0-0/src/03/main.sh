#!/bin/bash

if [ $# != 4 ]; then
echo "Invalid input: Enter 4 parameters"; exit 1; fi

for param in "$@"; do
if (echo "$param" | grep -Evq -e "^1$" -e "^2$" -e "^3$" -e "^4$" -e "^5$" -e "^6$"); then
echo "Invalid input: Enter 4 numeric parameters from 1 to 6"
exit 1
fi; done

bash color.sh $1 $2 $3 $4

