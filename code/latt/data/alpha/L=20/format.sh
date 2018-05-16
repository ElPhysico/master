#!/bin/bash
#for nRuns in 100000 #1000000 10000000
#	do
#		for p in 0.1 0.2 0.3 0.4
#			do
#				qsub -N FPT-nRuns=$nRuns -v nRuns=$nRuns,p=$p fpt.qsub
#		done
#done

for alpha in $(seq 0.1 0.1 0.9)
do
	./format -path=./fpt-alpha=$alpha.dat -val=0.25
done
		
