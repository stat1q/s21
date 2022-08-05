#!/bin/bash
cpu=$(echo "100 - $(mpstat | tail -n1 | awk '{print $NF}')" | bc)
vmstat_txt=$(vmstat | tail -n1)
mem_free=$(echo $vmstat_txt | awk '{print $4}')
mem_cache=$(echo $vmstat_txt | awk '{print $6}')
df_txt=$(df / | tail -n1)
disk_used=$(echo $df_txt | awk '{print $3}')
disk_available=$(echo $df_txt | awk '{print $4}')
echo \# HELP s21_cpu_usage CPU usage in percent.
echo \# TYPE s21_cpu_usage gauge
echo s21_cpu_usage $cpu 
echo \# HELP s21_mem_free Free memory in kilobytes.
echo \# TYPE s21_mem_free gauge
echo s21_mem_free $mem_free
echo \# HELP s21_mem_cache Cashed memory in kilobytes.
echo \# TYPE s21_mem_cache gauge
echo s21_mem_cache $mem_cache
echo \# HELP s21_disk_used Used disk in kilobytes.
echo \# TYPE s21_disk_used gauge
echo s21_disk_used $disk_used
echo \# HELP s21_disk_available Available disk in kilobytes.
echo \# TYPE s21_disk_available gauge
echo s21_disk_available $disk_available
