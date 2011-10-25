#!/bin/bash
# BenchMark PTrack2

echo "-- Starting Benchmark --"
echo "Obtaining 3 reference time"
./testSingle.sh 3
echo "Executing 4 parallel instance incrementaly"
./testParallel.sh 4
echo "Executing 4 parallel instance incrementaly using no threads"
./testParallelNT.sh 4
echo "-- Benchmark Finished --"
