#!/bin/bash

files=`ls perf-data/dur_*.csv`
outfile=perf-data/dur.csv
rm -f ${outfile}

echo "run,stages,time" > ${outfile}

for f in ${files}
do
	cat $f >> ${outfile}
done
