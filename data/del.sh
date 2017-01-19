#!/bin/bash

sort -t, -k1 $1 | awk -F',' '{
    if($1 != VALUE) {
    VALUE = $1;
    print $0;
    }
    else if($1 == VALUE) {}
}' > target

sort -t',' -k1 target > result.csv

rm target
