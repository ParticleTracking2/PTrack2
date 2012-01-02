#!/bin/bash
# BenchMark PTrack2

##########################
## Procesa la Imagen
## $1 = Tipo de test
## $2 = Iteracion del test
## $3 = Numero del test
## $4 = Dispositivo CUDA
##########################
SINGLE=0
PARALLEL=2
PARALLELCPU=3
CUDA_LIMIT=2
function doit {
	##############
	## Imagen 0 ##
	if [ $1 = $SINGLE -o $1 = $PARALLEL ]
	then
		if [[ $4 -eq 0 ]]
		then
			time ./PTrack2 chi2hdcuda -i ImgA00000$3.tif -out ./Out/data-$2-$3.txt -silent
		else
			time ./PTrack2 chi2hdcuda -i ImgA00000$3.tif -device $4 -out ./Out/data-$2-$3.txt -silent
		fi
	fi
	
	if [ $1 = $PARALLELCPU ]
	then
		time ./PTrack2 chi2hd -i ImgA00000$3.tif -out ./Out/data-cpu$2-$3.txt -silent
	fi
}

#################################################
## Lanza la tanda de procesamiento de imagenes
## $1 = Tipo de test
## $2 = Cantidad de tests
#################################################
function launch {
	mkdir Out
	local cudadev=0
	if [ $1 = $SINGLE ]
	then
		echo ">> Executing PTrack2: $2 Iteration"
		for ((i=1; i<=$2; i++))
		do
			doit $1 $i 0 0
		done
	fi

	if [ $1 = $PARALLEL ]
	then
		for ((i=1; i<=$2; i++))
		do
			echo ">> Executing PTrack2: $i Iteration"
			for ((j=1; j<=$i; j++))
			do
		        	echo -n "$j "
		        	
		        	if [[ $cudadev -lt $CUDA_LIMIT ]]
					then
						doit $1 $i $j $cudadev &
						let "cudadev=$cudadev+1"
					else
						cudadev=0
						doit $1 $i $j $cudadev &
					fi
			done
			wait
		done
	fi
	
	if [ $1 = $PARALLELCPU ]
	then
		for ((i=1; i<=$2; i++))
		do
			echo ">> Executing PTrack2 GPU: $i Iteration"
			
			for ((g=1; g<=$2; g++))
			do
				echo -n "GPU $g "
				if [[ $cudadev -lt $CUDA_LIMIT ]]
				then
					doit $PARALLEL $i $g $cudadev &
					let "cudadev=$cudadev+1"
				else
					cudadev=0
					doit $PARALLEL $i $g $cudadev &
				fi
			done
			
			for ((c=1; c<=$i; c++))
			do
				echo -n "CPU $c "
				doit $PARALLELCPU $i $c 0 &
			done
			wait
		done
	fi

	#echo ">> Verifing Data"
	#verify "7060604e898d35b5aa19b09d262b6162"
	rm -r Out
}

function main {
	echo ">> Starting Benchmark with Standar Image <<"
	echo ">> Obtaining time reference GPU (3 times)"
	time launch $SINGLE 3
	
	echo ">> Executing 8 parallel instance incrementaly GPU: 1 time"
	time launch $PARALLEL 8
	echo ">> Executing 8 parallel instance incrementaly GPU+CPU: 2 time"
	time launch $PARALLELCPU 8
}

( (time main)2>&1 ) > log-ref.txt 
