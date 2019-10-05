#!/bin/bash
clear
echo "
Please Select:
A. Display System Information
B. Display Disk Space
C. DIsplay Home Space Utilisation
Q. Quit
"
read -p "Enter Selection [0-3] > "
case $REPLY in 
q|Q) echo "Program terminated."
exit
;;
a|A) echo "Hostname: $HOSTNAME"
uptime
;;
b|B) df -h
;;
c|C) if [[ $(id -u) -eq 0 ]]; then
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
