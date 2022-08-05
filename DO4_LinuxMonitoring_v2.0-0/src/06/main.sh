#!/bin/bash
#sudo apt-get install goaccess
#goaccess -a -d -f /home/student/projects/DO4_LinuxMonitoring_v2.0-0/src/04/23Apr22.log -p /home/student/projects/DO4_LinuxMonitoring_v2.0-0/src/06/goaccess.conf -o /home/student/projects/DO4_LinuxMonitoring_v2.0-0/src/06/go-access.html

goaccess ../04/*.log --config-file=goaccess.conf
goaccess ../04/*.log -p goaccess.conf -o go-access.html

