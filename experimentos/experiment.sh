#!/bin/bash


nMax=1000

for (( i=1; i<=5; i++ ))
do
	nThreads=$((2**$i))
		
	for (( j=0; j<=3; j++ ))
	do
		nElems=$((200*2**j))
		nTotalElems=$(($nElems * 32))

		for (( k = 1; k<=15; k++))
		do
			mpirun -n 32 ./parallel-hybrid-sort -i "data/${nElems}input.txt" -m "$nMax" -f "data/${nElems}" -t "$nThreads" -l -p >> "data/log_${nElems}_${nThreads}_log.csv"
		done
	done
done
