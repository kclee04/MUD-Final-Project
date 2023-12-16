###Final Project for class CS2600 Fall 2023 with professor Nima Davarpanah, Cal Poly Pomona.

###Create a text-based game known as a MUD, Multi-User Dungeon.

MUD is one of the early network-based games that were played before the onset of graphical user interfaces became prevalent on modern systems today.

We use **ESP32** to act as **a video game system**.
In ESP32, a player will enter their movement (we use number keypad in this case) to move around.
When we move to each room, the description of the room will be printed on LCD.

**Requirements**: 
1) The **control inputs** by the user will be **sent to the server** using **SOCKET** COMMUNICATION.
It can either be UDP or TCP.
2) The **text description** of the room will be **displayed on the LCD** using **MQTT borker**.

We will use the **GCP (Google Could Platform) -- Compute Engine Instance** to act as **a server** where the game will be hosted.
Only one team member will have a GCP instance running. 

On the GCP, we create **a service** (a program) that runs in the background (as known as **a daemon process** in a Linux based OS).
This program uses MQTT and SOCKET communication to interact with the video game system, ESP32. 
This program is written **in C programming language** and be run as a service on the GCP instance.

The **C program** should have the following capabilities:
1) Set new users in the Start Room. Exp: /home/user/start_room
2) Accept player controls (North, South, East, West), using SOCKET communication that are passed from the ESP32
3) If subfolders exists, (North, South, East, West), open subfolder, **read "description.txt" file**, and **output the content to ESP32 using MQTT**.
   The message will be displayed on the LCD display of the ESP32. 

Finally, to make the dungeon layout, each team member creates a script that will cerate folders and subfolders with "description.txt" files. 
There are three special rooms: Start Room, Item Room, and Connector Room. Player should search for an item during the game.


