#!/bin/bash
sort -k 1,1 -k 2n distros.txt | while read distro version release; do
printf "Distro: %s\t Version: %s\tRelease: %s\n" \
$distro \
$version \
$release
done
