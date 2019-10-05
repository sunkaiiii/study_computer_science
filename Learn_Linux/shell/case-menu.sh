#!/bin/bash
clear
echo "
Please Select:
1. Display System Information
2. Display Disk Space
3. DIsplay Home Space Utilisation
0. Quit
"
read -p "Enter Selection [0-3] > "
case $REPLY in 
0) echo "Program terminated."
exit
;;
1) echo "Hostname: $HOSTNAME"
uptime
;;
2) df -h
;;
3) if [[ $(id -u) -eq 0 ]]; then
echo "Home Space Utilisation (All Users)"
du -sh /home/*
else
echo "Home Space Utilisation ($USER)"
du -sh $HOME
fi
;;
*) echo "Invalid entry" >&2
exit 1
;;
esac
