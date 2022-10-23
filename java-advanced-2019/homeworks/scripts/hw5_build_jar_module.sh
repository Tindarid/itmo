#!/bin/bash

echo Compiling
javac -d out -p ../../lib:../../artifacts --module-source-path ../java-modules --module ru.ifmo.rain.valeyev.implementor

echo Packing in jar
jar -c --file=implementor.jar --main-class=ru.ifmo.rain.valeyev.implementor.JarImplementor -C out/ru.ifmo.rain.valeyev.implementor .

echo Deleting temp
rm -r out
