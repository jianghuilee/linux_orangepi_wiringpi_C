#!/bin/bash 
gpio mode 5 out
	for((i=0;i<20;i++))
	do
			
			gpio write 5 1
			sleep 0.0015
			gpio write 5 0
			sleep 0.0185
			
	done
gpio mode 5 in


