#!/usr/bin/python

import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)

global counter
global delaytime
counter =0
dealtime=50.0/1000.0


def updown(channel):
    global dealytime
    GPIO.output(12,GPIO.HIGH)
    time.sleep(delaytime)
    GPIO.output(12,GPIO.LOW)

GPIO.setup(7,GPIO.IN)
GPIO.setup(12,GPIO.OUT)
GPIO.add_event_detect(12,GPIO.RISING,callback=updown)

print("program running, press enter to stop it")
a=input("press\n")
GPIO.output(12,GPIO.LOW)
