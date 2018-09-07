import RPi.GPIO as GPIO
from time import sleep
import sys

if len(sys.argv) == 1:
	N = 200
else:
	N = int(sys.argv[1])

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(3,GPIO.OUT)
for i in range(N):
	GPIO.output(3, True)
	sleep(0.5)
	GPIO.output(3, False)
	sleep(0.5)
