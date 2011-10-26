#!/bin/bash
# Prueba que funcione en forma basica Ptrack2

mkdir Out

function doit {
	time ./PTrack2 chi2hd -i ImgA000001.tif -d 8.65456 -w 1.24192 -out ./Out/data-$1.txt -silent -2filteri 0.5
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
		VERSTACK[${#VERSTACK[*]}]=$( md5sum "$file" )
	done

	for(( i=0; i<${#VERSTACK[@]}; ++i))
	do
		if [ "95b8c4996e4754e37444d68565630222" = "${VERSTACK[$i]:0:32}" ]
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
(time main $1) 2> ./simg/time-total.txt
echo "Test Ended"
rm -R Out/
