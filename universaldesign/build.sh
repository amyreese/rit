#!/bin/sh

CLEAN=$1

if [ "$CLEAN" = "clean" ] 
then
	make clean
fi

qmake && make && bin/unicalc

