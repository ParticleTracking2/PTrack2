#!/bin/bash
# Prueba que funcione en forma basica Ptrack2

mkdir Out

function doit {
	time ./PTrack2 chi2hd -i ImgA000000.tif -out ./Out/data-$1.txt -silent -2filteri 0.5
}

function main {
	for ((i=1; i<=$1; i++))
	do
		echo ">> Executing PTrack2 $i time"
		doit $i
	done

	echo "Verifing Data"
	verify

}

function verify {
	for file in ./Out/data-*.txt
	do
		VERSTACK[${#VERSTACK[*]}]=$( md5 "$file" )
	done

	for(( i=0; i<${#VERSTACK[@]}; ++i))
	do
		if [ "a4ccb4a07d64f161513f8f4bbe391b1f" = "${VERSTACK[$i]:0:32}" ]
		then
			echo "Data $i Correct"
		else
			echo "[ERROR] Data $i incorrect MD5Hash"
			echo "Data was "${VERSTACK[$i]:0:32}
			exit
		fi
	done
}

echo "Testing PTrack2 using standar parameters"
(time main $1) 2> ./std/time-total.txt
echo "Test Ended"
rm -R Out/
