#!/bin/bash
# BenchMark PTrack2

# Mac o no Mac?
if [ $1 = "Mac" -o $1 = "mac" ]
then
	MAC=1
else
	MAC=0
fi

cp ImgA000000.tif ImgA000001.tif
cp ImgA000000.tif ImgA000002.tif
cp ImgA000000.tif ImgA000003.tif
cp ImgA000000.tif ImgA000004.tif
cp ImgA000000.tif ImgA000005.tif
cp ImgA000000.tif ImgA000006.tif
cp ImgA000000.tif ImgA000007.tif
cp ImgA000000.tif ImgA000008.tif

##########################
## Procesa la Imagen
## $1 = Tipo de test
## $2 = Iteracion del test
## $3 = Numero del test
##########################
SINGLE=0
SINGLENT=1
PARALLEL=2
PARALLELNT=3
function doit {
	##############
	## Imagen 0 ##
	if [ $1 = $SINGLE -o $1 = $PARALLEL ]
	then
		time ./PTrack2 chi2hd -i ImgA00000$3.tif -out ./Out/data-$2-$3.txt -silent
	fi

	if [ $1 = $SINGLENT -o $1 = $PARALLELNT ]
	then
		time ./PTrack2 chi2hd -i ImgA00000$3.tif -out ./Out/data-$2-$3.txt -silent -nothreads
	fi
}

#######################################
# Verifica mediante un hash los datos
# $1 = Hash MD5
#######################################
function verify {
	for file in ./Out/data-*.txt
	do
		if [ "$MAC" = "1" ]
		then
			VERSTACK[${#VERSTACK[*]}]=$( md5 -q "$file" )
		else
			VERSTACK[${#VERSTACK[*]}]=$( md5sum "$file" )
		fi
	done

	for(( i=0; i<${#VERSTACK[@]}; ++i))
	do
		if [ "$1" = "${VERSTACK[$i]:0:32}" ]
		then
			echo -n "."
		else
			echo "[ERROR] Data $i incorrect MD5Hash"
			echo "Data was "${VERSTACK[$i]:0:32}
			exit
		fi
	done
	echo " OK"
}

#################################################
## Lanza la tanda de procesamiento de imagenes
## $1 = Tipo de test
## $2 = Cantidad de tests
#################################################
function launch {
	mkdir Out
	if [ $1 = $SINGLE -o $1 = $SINGLENT ]
	then
		echo ">> Executing PTrack2: $2 Iteration"
		for ((i=1; i<=$2; i++))
		do
			doit $1 $i 0
		done
	fi

	if [ $1 = $PARALLEL -o $1 = $PARALLELNT ]
	then
		for ((i=1; i<=$2; i++))
		do
			echo ">> Executing PTrack2: $i Iteration"
			for ((j=1; j<=$i; j++))
			do
		        	echo -n "$j "
		        	doit $1 $i $j &
			done
			wait
		done
	fi

	echo ">> Verifing Data"
	verify "7060604e898d35b5aa19b09d262b6162"
	rm -r Out/
}

function main {
	echo ">> Starting Benchmark with Standar Image <<"
	echo ">> Obtaining time reference (3 times)"
	time launch $SINGLE 3
	echo ">> Obtaining time reference using no threads (3 times)"
	time launch $SINGLENT 3
	
	echo ">> Executing 8 parallel instance incrementaly: 1 time"
	time launch $PARALLEL 8
	echo ">> Executing 8 parallel instance incrementaly: 2 time"
	time launch $PARALLEL 8
	echo ">> Executing 8 parallel instance incrementaly: 3 time"
	time launch $PARALLEL 8
	
	echo ">> Executing 8 parallel instance incrementaly using no threads: 1 time"
	time launch $PARALLELNT 8
	echo ">> Executing 8 parallel instance incrementaly using no threads: 2 time"
	time launch $PARALLELNT 8
	echo ">> Executing 8 parallel instance incrementaly using no threads: 3 time"
	time launch $PARALLELNT 8
	echo ">> Benchmark Finished <<"	
}

( (time main)2>&1 ) > log-ref.txt 

rm ImgA000001.tif ImgA000002.tif ImgA000003.tif ImgA000004.tif ImgA000005.tif ImgA000006.tif ImgA000007.tif ImgA000008.tif
