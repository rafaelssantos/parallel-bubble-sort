#!/bin/bash


nMax=1000

for (( j=0; j<=3; j++ ))
do
	nElems=$((200*2**j))
	nTotalElems=$(($nElems * 32))
	
	./parallel-hybrid-sort -f "data/${nElems}" -n "$nTotalElems" -m "$nMax" -l > "data/seqlog_${nElems}_log.csv"
	for (( k = 1; k<=10; k++))
	do
		./parallel-hybrid-sort -f "data/${nElems}" -i "data/${nElems}input.txt" -m "$nMax" -l >> "data/seqlog_${nElems}_log.csv"
	done
done





for (( i=1; i<=5; i++ ))
do
	nThreads=$((2**$i))
		
	for (( j=0; j<=3; j++ ))
	do
		nElems=$((200*2**j))
		nTotalElems=$(($nElems * 32))
		
		#./parallel-hybrid-sort -f "data/${nElems}" -n "$nTotalElems" -m "$nMax" -t "$nThreads" -l -p > "data/log_${nElems}_${nThreads}_log.csv"
		for (( k = 1; k<=10; k++))
		do
			./parallel-hybrid-sort -f "data/${nElems}" -i "data/${nElems}input.txt" -m "$nMax" -t "$nThreads" -l -p >> "data/log_${nElems}_${nThreads}_log.csv"
		done
	done
done