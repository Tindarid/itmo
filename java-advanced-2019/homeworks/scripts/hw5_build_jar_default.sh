#!/bin/bash

prefix=../java
myjava=ru/ifmo/rain/valeyev/implementor
goshajava=info/kgeorgiy/java/advanced/implementor

echo Compiling
javac $prefix/$goshajava/JarImpler.java
javac -cp $prefix $prefix/$myjava/JarImplementor.java

echo Packing in jar
jar cfe implementor.jar ru.ifmo.rain.valeyev.implementor.JarImplementor -C $prefix $goshajava -C $prefix $myjava

echo Deleting temp .class files
rm $prefix/$myjava/*.class
rm $prefix/$goshajava/*.class
