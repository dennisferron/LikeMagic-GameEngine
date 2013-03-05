#!/bin/bash

delFile=$1

if [ -e $delFile ]; then
	: #echo "File to delete is" $delFile
else
	echo "File does not exist:" $delFile
	exit
fi

delTime=`date -r $delFile +%s`
echo "Time of file" $delFile "is" $delTime

shift

for checkFile
do
	if [ -e $checkFile ]; then
		: #echo  "File to check is " $checkFile
	else
		echo "File does not exist: " $checkFile
		continue
	fi

	checkTime=`date -r $checkFile +%s`
	#echo "Time of file" $checkFile "is" $checkTime

	if [ $delTime -ne $checkTime ]; then
		if [ $delTime -lt $checkTime ]; then
			echo "File" $delFile "is older, deleting."
			rm $delFile
			exit
		#else
			#echo "File" $delFile "is newer."
		fi
	else
		echo "File times are equal."
	fi

done

