#!/bin/bash

if [ "$#" -eq 1 ]; then
  starting_location="$1"
  cd $starting_location
  mkdir north
  cd north
else
  starting_location="$(pwd)"
  cd $starting_location
  mkdir startroom
  cd startroom
fi

echo "A cold room" > desc.txt

# second room
mkdir east
cd east
echo "A dark room" > desc.txt

# third room
mkdir east
mkdir west
cd west
touch goback.txt
cd ..
cd east
touch desc.txt
echo "A scary room" > desc.txt

# fourth room
mkdir north
mkdir south
mkdir west
cd west
touch goback.txt
cd .. 
cd south # item room
echo "Found sword" > item.txt
mkdir north
cd north
touch goback.txt
cd ..
cd ..
cd north
touch desc.txt
echo "A bright room" > desc.txt

# sixth room
mkdir north
mkdir south
cd south
touch goback.txt
cd ..
cd north
touch desc.txt
echo "A warm room" > desc.txt

#seventh room
mkdir east
mkdir west
mkdir south
cd south
touch goback.txt
cd ..
cd west #eighth room
echo "A windy room" > desc.txt
mkdir east
cd east
touch goback.txt
cd .. # seventh
cd ..
cd east
touch desc.txt
echo "A crowded room" > desc.txt

# ninth room
mkdir east
mkdir west
cd west
touch goback.txt
cd ..
cd east
touch desc.txt
echo "A small room" > desc.txt

# connector room
mkdir west
cd west
touch goback.txt
cd ..
mkdir east
cd east
echo "A damp room" > desc.txt
# run next person bash script in here
mkdir west
cd west
touch goback.txt
cd ..
mkdir north
cd north
