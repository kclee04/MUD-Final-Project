#!/bin/bash
if [ "$#" -eq 1 ]; then
        starting_location="$1"
else
        starting_location="$(pwd)"
fi

#creating start room and connections.
mkdir $starting_location/start_room

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