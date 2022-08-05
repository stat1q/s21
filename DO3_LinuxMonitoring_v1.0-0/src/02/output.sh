#!/bin/bash

echo HOSTNAME = $(hostname)
echo TIMEZONE = $(timedatectl) | awk '{print $1,$2,$22,$14,$8}'
echo USER = $(whoami)
echo OS = $(cat /etc/issue) | awk '{print $1,$2,$3,$4,$5}'
echo DATE = $(date) | awk '{print $1,$2,$4,$5,$6,$7}'
echo UPTIME = $(uptime -p)
echo UPTIME_SEC = $(cat /proc/uptime) | awk '{print $1,$2,$3" sec"}'
echo IP = $(hostname -I)
echo MASK = $(netstat -rn) | awk '{print $1,$2,$25}'
echo GATEWAY = $(ip r show) | awk '{print $1,$2,$5}'
echo RAM_TOTAL = $(free) | awk '{printf("%s %s ",$1,$2); printf("%.3f Gb\n", $10/1048576)}'
echo RAM_USED = $(free) | awk '{printf("%s %s ",$1,$2); printf("%.3f Gb\n", $11/1048576)}'
echo RAM_FREE = $(free) | awk '{printf("%s %s ",$1,$2); printf("%.3f Gb\n", $12/1048576)}'
echo SPACE_ROOT = $(df /) | awk '{printf("%s %s ",$1,$2); printf("%.2f MB\n", $11/1024)}'
echo SPACE_ROOT_USED = $(df /) | awk '{printf("%s %s ",$1,$2); printf("%.2f MB\n", $12/1024)}'
echo SPACE_ROOT_FREE = $(df /) | awk '{printf("%s %s ",$1,$2); printf("%.2f MB\n", $13/1024)}'