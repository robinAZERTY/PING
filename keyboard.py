# send all keyboard events to Arduino Serial port (115200 baud com 12)

import serial
import pygame
from pygame.locals import *

# open serial port
ser = serial.Serial('COM3', 115200, timeout=1)


# initialize pygame 
pygame.init()
pygame.display.set_mode((100, 100))

# main loop
while True:
    # get all keyboard events since last loop
    for event in pygame.event.get():
        # if key is pressed or released
        if event.type == KEYDOWN or event.type == KEYUP:
            
            to_send = str(event.key)+","+str(event.type)+"\n"
            ser.write(to_send.encode()) 
            print(to_send)
            
ser.close()  