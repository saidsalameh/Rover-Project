#include <iostream>
#include <vector>
#include <cstdint>


/*
// ======== Hardware Configuration ====

// GPIO 15 RXD ---> Pin 10
// GPIO 14 TXD ---> Pin 8
// Ground      ---> Pin 9

// Baud rate : 115200 baud
// In order to use a GPIO : $ sudo usermod -a -G gpio <username>


// ======== Software flow ===========

UART STM32 --- (data structure format) ---> UART Raspberry PI --- (data structure and parsing) --->
Send data via ROS2 Node ---> Reception ROS2 node on VM

// Add Ping-pong Stm32 && Raspberry Pi in order to check UART connection


// ======= Data structure format ====

Reception :
----------
Use the same data structure implemented on stm32
Identify the header to know what data we are receiving ?
UART Frame ?
CRC ?

Transmition :
-------------
Format : String 
[Transmit infomation for testing Pi node --> Vm node]
[start value : header][Time of package reception / acquisition][Data][CRC]

UART Rader node :
-----------------
1. How to access UART on Raspberry Pi Os
2. How to read from serial port in linux/C++/C
   Hint : serial linux library / open() / read() / close()

3. Pseudo code :
----------------
** Initialize UART
** Configure baudrate
** Thread / loop : read --> pacage into ros message --> publish the message --> close on shutdown

Configure th pi package : package.xml + CMakelist

*/

