#!/bin/bash

#if path is provided, the connecting start_room will be called NORTH
if [ "$#" -eq 1 ]; then
        starting_location="$1"
        mkdir $starting_location/NORTH
        cd $starting_location/NORTH
else
        starting_location="$(pwd)"
        mkdir $starting_location/start_room
        cd $starting_location/start_room
fi

#check if start room was created
if [ $? -eq 0 ]; then
        cd $starting_location/start_room
        echo "Start room." > "desc.txt"

        mkdir EAST
        cd EAST
        echo "R1" > "desc.txt"

        mkdir NORTH
        cd NORTH
        echo "R2" > "desc.txt"
        cd ..

        mkdir EAST
        cd EAST
        echo "R3" > "desc.txt"

        mkdir EAST
        cd EAST
        echo "R4" > "desc.txt"

        mkdir NORTH
        cd NORTH
        echo "R5" > "desc.txt"
        cd ..

        mkdir EAST
        cd EAST
        echo "R6" > "desc.txt"

        mkdir SOUTH
        cd SOUTH
        echo "R7" > "desc.txt"

        mkdir EAST
        cd EAST
        echo "R8" > "desc.txt"

        mkdir EAST
        cd EAST
        echo "R9" > "desc.txt"

        mkdir NORTH
        cd NORTH
        echo "R10" > "desc.txt"
        cd ..

        mkdir EAST
        cd EAST
        echo "Item" > "desc.txt"

        mkdir NORTH
        cd NORTH
        echo "Connector" > "desc.txt"
else
        echo "Failed to generate rooms."
fi
