#!/bin/bash


nMax=1000

for (( j=0; j<=3; j++ ))
do
	nElems=$((200*2**j))
	nTotalElems=$(($nElems * 32))
	
	./parallel-hybrid-sort -f "data/${nElems}" -n "$nTotalElems" -m "$nMax" -l > "data/seqlog_${nElems}_log.csv"
	for (( k = 1; k<=10; k++))
	do
		mpirun -n 1 ./parallel-hybrid-sort -f "data/${nElems}" -i "data/${nElems}input.txt" -l >> "data/seqlog_${nElems}_log.csv"
	done
done





for (( i=1; i<=5; i++ ))
do
	nProcess=$((2**$i))
		
	for (( j=0; j<=3; j++ ))
	do
		nElems=$((200*2**j))
		nTotalElems=$(($nElems * 32))
		
		#./parallel-hybrid-sort -f "data/${nElems}" -n "$nTotalElems" -m "$nMax" -t "$nProcess" -l -p > "data/log_${nElems}_${nProcess}_log.csv"
		for (( k = 1; k<=10; k++))
		do
			mpirun -n 32 ./parallel-hybrid-sort -f "data/${nElems}" -i "data/${nElems}input.txt" -t "$nProcess" -l -p >> "data/log_${nElems}_${nThreads}_log.csv"
		done
	done
done