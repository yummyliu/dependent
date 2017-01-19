#!/bin/bash

sort -t, -k1 $1 | awk -F',' '{
    if($1 == VALUE) {
    VALUE = "";
    print $0;
    }
    else if($1 != VALUE) {VALUE=$2;}
}' > target

sort -t',' -k1 target > data.csv
rm target

