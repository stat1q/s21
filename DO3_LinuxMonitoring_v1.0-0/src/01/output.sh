#!/bin/bash

if ( echo "$1" | grep -E -q "^-?[[:digit:]]+$" ); then
echo "Invalid input: Please enter a string"
else
echo "$1"
fi
