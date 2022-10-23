#!/bin/bash

modulepath=../../lib:../../artifacts 
classpath=../java
my=ru.ifmo.rain.valeyev
gosha=info.kgeorgiy.java.advanced
exec="java -cp $classpath -p $modulepath -m"
usage="Usage: hw_test [number] [hard or easy]"

if [ $# != 2 ]
then
  echo $usage
  exit
fi

if [[ $2 == advanced && $1 == 3 ]]
then
  $exec $gosha.student AdvancedStudentGroupQuery $my.student.StudentDB
  exit
fi

if [[ $2 != easy && $2 != hard ]]
then
  echo $usage
  exit
fi

if [ $1 == 1 ]
then
  if [ $2 == easy ]
  then
    $exec $gosha.walk Walk $my.walk.RecursiveWalk
  else
    $exec $gosha.walk RecursiveWalk $my.walk.RecursiveWalk
  fi
elif [ $1 == 2 ]
then
  if [ $2 == easy ]
  then
    $exec $gosha.arrayset SortedSet $my.arrayset.ArraySet
  else
    $exec $gosha.arrayset NavigableSet $my.arrayset.ArraySet
  fi
elif [ $1 == 3 ]
then
  if [ $2 == easy ]
  then
    $exec $gosha.student StudentQuery $my.student.StudentDB
  else
    $exec $gosha.student StudentGroupQuery $my.student.StudentDB
  fi
elif [ $1 == 4 ]
then
  if [ $2 == easy ]
  then
    $exec $gosha.implementor interface $my.implementor.Implementor
  else
    $exec $gosha.implementor class $my.implementor.Implementor
  fi
elif [[ $1 == 5 || $1 == 6 ]]
then
  if [ $2 == easy ]
  then
    $exec $gosha.implementor jar-interface $my.implementor.JarImplementor
  else
    $exec $gosha.implementor jar-class $my.implementor.JarImplementor
  fi
elif [ $1 == 7 ]
then
  if [ $2 == easy ]
  then
    $exec $gosha.concurrent scalar $my.concurrent.IterativeParallelism
  else
    $exec $gosha.concurrent list $my.concurrent.IterativeParallelism
  fi
elif [ $1 == 8 ]
then
  if [ $2 == easy ]
  then
    $exec $gosha.mapper scalar $my.mapper.ParallelMapperImpl,$my.mapper.IterativeParallelism
  else
    $exec $gosha.mapper list $my.mapper.ParallelMapperImpl,$my.mapper.IterativeParallelism
  fi
elif [ $1 == 9 ]
then
  if [ $2 == easy ]
  then
    $exec $gosha.crawler easy $my.crawler.WebCrawler
  else
    $exec $gosha.crawler hard $my.crawler.WebCrawler
  fi
else
  echo $usage
fi
