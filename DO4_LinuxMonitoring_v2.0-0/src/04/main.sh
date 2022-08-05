#!/bin/bash
sudo chmod +x codes.sh createlog.sh numgen.sh
source ./numgen.sh
source ./codes.sh

function savelog {
filename=${1//"/"/""}".log"
./createlog.sh  $1 | sort | cut -f2-4 > $filename 
}

savelog "23/Apr/22"
savelog "24/Apr/22"
savelog "25/Apr/22"
savelog "26/Apr/22"
savelog "27/Apr/22"
