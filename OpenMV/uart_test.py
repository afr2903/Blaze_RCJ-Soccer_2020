# UART Control
#
# This example shows how to use the serial port on your OpenMV Cam. Attach pin
# P4 to the serial input of a serial LCD screen to see "Hello World!" printed
# on the serial LCD display.

import time
from pyb import UART
import ustruct

# Always pass UART 3 for the UART number for your OpenMV Cam.
# The second argument is the UART baud rate. For a more advanced UART control
# example see the BLE-Shield driver.
uart = UART(3, 19200, timeout_char=200)
threshold= [22, 99, -8, 26, -11, 15]
b_threshold= [0,0,0,0,0,0]
for i in range(6):
    b_threshold[i]= ustruct.pack("<b", threshold[i])

while(True):
    uart.write('a')
    #for i in range(6):
        #uart.write(b_threshold[i])
        #print(b_threshold[i])
    #time.sleep(100)
