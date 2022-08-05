#!/bin/bash

if [ $# != 1 ]; then
echo "Invalid input: Enter 1 parameter"
exit 1
else
bash output.sh $1
fi
