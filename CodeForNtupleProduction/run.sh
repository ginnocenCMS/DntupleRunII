CONFIGFILE=loopnew.C
DESTINATION=$1
OUTFILE=$3
INFILE=$2

#root -l -b -q  $CONFIGFILE++\(\"${INFILE}\",\"${OUTFILE}\"\)
root -l -b -q  $CONFIGFILE+\(\"${INFILE}\",\"${OUTFILE}\"\)
mv ${OUTFILE} ${DESTINATION}/${OUTFILE}