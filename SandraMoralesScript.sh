#!/bin/bash
if [ "$#" -eq 1 ]; then
  starting_location="$1"
else
  starting_location="$(pwd)"
fi

# echo "$starting_location"

# create start and connector rooms
mkdir $starting_location/start_room

# check if start room was created
if [ $? -eq 0 ]; then
  cd $starting_location/start_room
  echo "The room is dim with purple hue." > "desc.txt"

#second room
mkdir east
cd east
echo "It feels humid in this room." > "desc.txt"

#third room
mkdir west
mkdir east
cd west
cd ..
cd east
echo "The room is hot and dry." > "desc.txt"

#fourth room
mkdir west
mkdir east
cd west
cd ..
cd east
echo "The room is freezing." > "desc.txt"

#fifth room
mkdir north
mkdir south
cd north
cd ..

cd south
echo "The walls have writing." > "desc.txt"

#sixth room
mkdir north
mkdir south
cd north
cd ..

cd south
echo "The floor is sticky." > "desc.txt"

#seventh room
mkdir east
mkdir west
cd west
cd ..

cd east #item room
echo "You found a ring. Got ring item!" > "desc.txt"


#eighth room
mkdir east
mkdir west
cd west
cd ..

cd east
echo "Ceiling emits dark red light" > "desc.txt"

#ninth room
mkdir south
mkdir north
cd south
cd ..

cd north
echo "It is covered in plants." > "desc.txt"

#tenth room

mkdir south
mkdir north
cd south
cd ..

cd north
echo "This room smells nice." > "desc.txt"
else
  echo "Failed to generate rooms"
fi