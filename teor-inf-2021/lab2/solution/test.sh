OUT=tmp_out
UNP=tmp_unp
TO_TEST=jpeg80

rm -f $OUT
rm -f $UNP

INP_SUM=0
OUT_SUM=0
for INP in ../$TO_TEST/*
do
  ./coder $INP $OUT
  ./decoder $OUT $UNP

  INP_SIZE=$(stat --printf="%s" $INP)
  OUT_SIZE=$(stat --printf="%s" $OUT)
  INP_SUM=$(( $INP_SUM + $INP_SIZE ))
  OUT_SUM=$(( $OUT_SUM + $OUT_SIZE ))

  echo ${INP##*/}: $INP_SIZE -\> $OUT_SIZE

  PREV=$(md5sum $INP | awk '{print $1}')
  AFTE=$(md5sum $UNP | awk '{print $1}')

  if [ "$PREV" != "$AFTE" ]; then
      echo "bad :(";
      exit 1
  fi

  rm -f $OUT
  rm -f $UNP
done

echo "Input sum of files: $INP_SUM";
echo "Output sum of files: $OUT_SUM";
GAIN=`echo "scale=2; 100*($INP_SUM - $OUT_SUM)/($INP_SUM)" | bc`
echo "Total gain: $GAIN%";
