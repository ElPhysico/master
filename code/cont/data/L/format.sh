#!/bin/bash
#for nRuns in 100000 #1000000 10000000
#	do
#		for p in 0.1 0.2 0.3 0.4
#			do
#				qsub -N FPT-nRuns=$nRuns -v nRuns=$nRuns,p=$p fpt.qsub
#		done
#done

#for alpha in $(seq 0.1 0.1 0.9)
for L in 10 20 50 100 200 500 1000
#for D in 1 2 3 4 5 10 15 20
do
	./format -path=./MFPT-L=$L.dat -val=0.0
done
		
