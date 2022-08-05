#!/bin/bash
sudo chmod +x node.sh

while sleep 3
do
    ./node.sh > /var/www/node/metrics.txt
done
