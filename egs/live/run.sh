#!/usr/bin/env bash

BARISTAROOT=../..
export PATH=$BARISTAROOT/bin:$PATH

rm report.txt
touch report.txt
barista conf/actors.ini conf/graph.dot
