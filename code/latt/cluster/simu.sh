#!/bin/bash
#for nRuns in 100000 #1000000 10000000
#	do
#		for p in 0.1 0.2 0.3 0.4
#			do
#				qsub -N FPT-nRuns=$nRuns -v nRuns=$nRuns,p=$p fpt.qsub
#		done
#done

for N in 10000
do
	for L in 200
	do
		for D in 1
		do
			for alpha in 0.5
			do
				for p in $(seq 0 0.05 0.95)
				do
					qsub -N FPT++alpha=$alpha++p=$p -v N=$N,L=$L,D=$D,alpha=$alpha,p=$p fpt.qsub
				done
			done
		done	
	done
done
		
