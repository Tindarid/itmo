#!/bin/bash

myjava=../java/ru/ifmo/rain/valeyev/implementor
goshajava=../java/info/kgeorgiy/java/advanced/implementor

javadoc -d doc -private $myjava/*.java $goshajava/*.java
