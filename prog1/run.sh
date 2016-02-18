#!/bin/bash
echo "Starting"
for i in `seq 1 10`
do
	echo $i
	./randmst 2 100 100 0
	echo "Done running MST"
	python plot.py
done
echo "Finished program"