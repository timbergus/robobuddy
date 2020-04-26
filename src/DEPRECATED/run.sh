#!/bin/bash

path=./output/nmea-parser

if [ ! -f $path ]; then
    make && ./output/nmea-parser # Build
else
    make clean && make && ./output/nmea-parser # Rebuild
fi
