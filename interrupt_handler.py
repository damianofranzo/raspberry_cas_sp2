#!/usr/bin/python

import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)

global counter;
counter =0;


def updown(channel):
    global counter
    counter=counter+1
    #voltage up on pin X
GPIO.setup(17,GPIO.IN)
GPIO.add_event_detect(17,GPIO.BOTH,callback=updown)

while(1):
    print("counter= "+str(counter))
    time.sleep(1)