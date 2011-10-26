#!/bin/bash
# BenchMark PTrack2

function main {
	echo "Obtaining time reference (3 times)"
	./std/testSingle.sh 3
	echo "Obtaining time reference using no threads (3 times)"
	./std/testSingleNT.sh 3
	echo "Executing 8 parallel instance incrementaly"
	./std/testParallel.sh 8
	echo "Executing 8 parallel instance incrementaly using no threads"
	./std/testParallelNT.sh 8
	echo "-- Benchmark Finished --"	
}

function main2 {
	echo "Obtaining time reference (3 times)"
	./simg/testSingle.sh 3
	echo "Obtaining time reference using no threads (3 times)"
	./simg/testSingleNT.sh 3
	echo "Executing 8 parallel instance incrementaly"
	./simg/testParallel.sh 8
	echo "Executing 8 parallel instance incrementaly using no threads"
	./simg/testParallelNT.sh 8
	echo "-- Benchmark Finished --"	
}

echo "-- Starting Benchmark with Standar Image --"
(time main) 2> log-ref.txt 
echo "-- Starting Benchmark with Second Image --"
(time main2) 2> log-img2.txt
