#!/bin/bash
while [[ $REPLY != 0 ]]; do
clear
echo "
Please Select:

1.Display System Information
2.Display Disk Space
3.Display Home Space Utilisation
0.Quit
"

read -p "Enter selection [0-3] > "

if [[ $REPLY =~ ^[0-3]$ ]]; then
	if [[ $REPLY == 0 ]]; then
		echo "Program terminated."
		exit
	fi
	if [[ $REPLY == 1 ]]; then
		echo "Hostname: $HOSTNAME"
		uptime
		exit
	fi
	if [[ $REPLY == 2 ]]; then
		df -h 
		exit
	fi
	if [[ $REPLY == 3 ]]; then
		if [[ $(id -u) -eq 0 ]]; then
			echo "Home Space Utilisation (All Users)"
			du -sh /home/*
		else
			echo "Home Space Utilisation ($USER)"
			du -sh $HOME
		fi
		exit
	fi
else
	echo "Invalid entry." >&2
	exit 1
fi
done
echo "Program terminated"
