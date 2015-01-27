#!/bin/sh

read a
a=" "
if [ -n $a ]; then 
    echo -n "--"
    echo -n "is not empty 1"
    echo -n "--"
fi
if [ -n "$a" ]; then 
    echo -n "--"
    echo -n "is not empty 2"
    echo -n "--"
fi
if [ $a ]; then 
    echo -n "--"
    echo -n "is not empty 3"
    echo -n "--"
fi
if [ "$a" ]; then 
    echo -n "--"
    echo -n "is not empty 4"
    echo -n "--"
fi
if [ 0 ]; then 
    echo -n "--"
    echo -n "is not empty 5"
    echo -n "--"
fi
if [ -n 0 ]; then 
    echo -n "--"
    echo -n "is not empty 6"
    echo -n "--"
fi
if [ -n -1 ]; then 
    echo -n "--"
    echo -n "is not empty 7"
    echo -n "--"
fi
if [ -n 1 ]; then 
    echo -n "--"
    echo -n "is not empty 8"
    echo -n "--"
fi
