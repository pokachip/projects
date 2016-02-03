import RPi.GPIO as GPIO
import time

print "GPIO Clear"

GPIO.setmode(GPIO.BCM)

for i in range(2,28):
    GPIO.setup(i, GPIO.OUT)
for i in range(2,28):
    GPIO.output(i, GPIO.LOW)

print "GPIO.cleanup()"
GPIO.cleanup()
    
