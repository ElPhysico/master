#!/bin/bash
#for nRuns in 100000 #1000000 10000000
#	do
#		for p in 0.1 0.2 0.3 0.4
#			do
#				qsub -N FPT-nRuns=$nRuns -v nRuns=$nRuns,p=$p fpt.qsub
#		done
#done

for N in 100000 1000000 10000000
do
	for L in 200
	do	
		for p in $(seq 0.00 0.05 0.95)
		do
			qsub -N MFPT++p=$p++N=$N -v N=$N,p=$p,L=$L mfpt.qsub
		done
	done
done
		
