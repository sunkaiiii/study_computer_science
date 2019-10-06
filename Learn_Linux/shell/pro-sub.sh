#!/bin/bash
while read attr links owner group size date time filename; do
	cat <<- EOF
Filename:	$filename
Size:	$size
Owner:	$owner
Group:	$group
Modified:	$date $time
Links:	$links
Attributes:	$attr
EOF
done < <(ls -l | tail -n +2)


