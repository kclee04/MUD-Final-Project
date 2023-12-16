## Final Project for class CS2600 Fall 2023 with professor Nima Davarpanah, Cal Poly Pomona.

### Create a text-based game known as a MUD, Multi-User Dungeon.

MUD is one of the early network-based games that were played before the onset of graphical user interfaces became prevalent on modern systems today.

#### ABOUT ESP32 
We use **ESP32** to act as **a video game system**.
In ESP32, a player will enter their movement (we use number keypad in this case) to move around.
When we move to each room, the description of the room will be printed on LCD.

**Requirements**: 
1) The **control inputs** by the user will be **sent to the server** using **SOCKET** COMMUNICATION.
It can either be UDP or TCP.
2) The **text description** of the room will be **displayed on the LCD** using **MQTT borker**.

#### ABOUT GCP
We will use the **GCP (Google Could Platform) -- Compute Engine Instance** to act as **a server** where the game will be hosted.
Only one team member will have a GCP instance running. 

On the GCP, we create **a service** (a program) that runs in the background (as known as **a daemon process** in a Linux based OS).
This program uses MQTT and SOCKET communication to interact with the video game system, ESP32. 
This program is written **in C programming language** and be run as a service on the GCP instance.

#### ABOUT C PROGRAMMING
The **C program** should have the following capabilities:
1) Set new users in the Start Room. Exp: /home/user/start_room
2) Accept player controls (North, South, East, West), using SOCKET communication that are passed from the ESP32
3) If subfolders exists, (North, South, East, West), open subfolder, **read "description.txt" file**, and **output the content to ESP32 using MQTT**.
   The message will be displayed on the LCD display of the ESP32. 

Finally, to make the dungeon layout, each team member creates a script that will **cerate folders and subfolders** with "description.txt" files. 
There are three special rooms: Start Room, Item Room, and Connector Room. Player should search for an item during the game.

#### ABOUT BASH SCRIPT
**The BASH Script** that each member create should hav the following capabilities:
1) The script will accept a path that will be used to start generating the folder/subfolder and description file.
   **Exp 1**: When running the script ./layout.sh /home/user/startroom, the script will start generating from /home/user/startroom.
   **Exp 2**: When running the script ./layout.sh/home/user/folder/folder/folder, the script will start generating from /home/user/folder/folder/folder.
2) The script will create new subfolders (North, South, East, West) and files "description.txt" that will describe the room to the user.
3) One of the rooms should have a special item. This can be included in the "description.txt"
4) To make the game challenging for players, each team members will create their script that will create 10 rooms with one start room, one item room, and one connector room.
5) NOTE: **Connector room** will be **the path used for remaining team member** scripts to build complex room designs.
