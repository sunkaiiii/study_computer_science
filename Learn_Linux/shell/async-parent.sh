#!/bin/bash
echo "Parent: starting..."
echo "Parent: launching child script..."
"async-child.sh" &
pid=&!
echo "Parent: child (PID=$pid) launched."
echo "Parent: continuing..."
sleep 2
echo "Parent: pasing to wait for child to finish..."
wait &pid
echo "Parent: child is finished. Continuing..."
echo "Parent: parent is done. Exiting."

