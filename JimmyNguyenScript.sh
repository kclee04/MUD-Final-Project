#!/bin/bash

if [ "$#" -eq 1 ]; then
  starting_location="$1"
else
  starting_location="$(pwd)"
fi

# echo "$starting_location"

# create start room and connections
mkdir $starting_location/start_room

# check if start room was created 
if [ $? -eq 0 ]; then
  cd $starting_location/start_room
  echo "This room stinks" > "desc.txt"
  mkdir north east

  # Generate North section
  cd north
  echo "Oh wow a skeleton in the room." > "desc.txt"
  mkdir north

  cd north
  echo "That's a lot of pathways." > "desc.txt"
  mkdir north west east

  cd north
  echo "Rats. This is a dead end." > "desc.txt"
  cd ..

  cd west 
  echo "Bats. This is also a dead end." > "desc.txt"
  cd ..

  cd east 
  echo "Oh a sword! Sword item received." > "desc.txt"
  cd ..

  # currently at start location
  cd ../..

  # Generate East section
  cd east
  echo "Blood leading to over there..." > "desc.txt"
  mkdir east

  cd east
  echo "The trail doesn't end" > "desc.txt"
  mkdir north

  cd north
  echo "Wow, now it's a trail of apples" > "desc.txt"
  mkdir east

  cd east
  echo "Weird painting on the wall." > "desc.txt"
  mkdir north

  cd north
  echo "There's a portal in this room." > "desc.txt"
else
  echo "Failed to generate rooms"
fi
