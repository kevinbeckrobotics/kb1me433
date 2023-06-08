from ulab import numpy as np # to get access to ulab numpy functions
import math
#from mu import plotter as pt
import board
import time
import digitalio
import analogio
#import adafruit_displayio_ssd1306 as display

#Declare and fill arrays (dependent and data)
ind = []
data = []

array_size = 1024
for i in range(array_size):
    x = i * 10 * math.pi / array_size
    y = i * 15 * math.pi / array_size - 0.1
    z = i * 5 * math.pi / array_size + 0.1
    sin_val = math.sin(x) + math.sin(y) + math.sin(z)
    ind.append(i)
    data.append(sin_val)

# Fourier transform

ffdata = np.array(data)

# Create analog pin

adc_pin_a0 = analogio.AnalogIn(board.A0)

for j in range(array_size):
    adc_pin_a0 = ffdata[j]
    if j % 11 == 0:
        print((0.025 * j,adc_pin_a0))
    time.sleep(0.025)
