# Automatic RGB565 Color Tracking Example
#
# This example shows off single color automatic RGB565 color tracking using the OpenMV Cam.

import sensor, image
import time
from pyb import UART
import ustruct
uart = UART(3, 19200, timeout_char=200)

#print("Letting auto algorithms run. Don't put anything in front of the camera!")

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 500)
#sensor.set_auto_gain(False) #7.04294  must be turned off for color tracking
sensor.set_auto_whitebal(False,[-6.02073, -3.454361, -0.4176831]) # must be turned off for color tracking
clock = time.clock()

"""# Capture the color thresholds for whatever was in the center of the image.
r = [(300//2)-(50//2), (220//2)-(50//2), 80, 80] # 50x50 center of QVGA.

#print("Auto algorithms done. Hold the object you want to track in front of the camera in the box.")
#print("MAKE SURE THE COLOR OF THE OBJECT YOU WANT TO TRACK IS FULLY ENCLOSED BY THE BOX!")
for i in range(150):
    img = sensor.snapshot()
    img.draw_rectangle(r)

#print("Learning thresholds...")
threshold = [50, 50, 0, 0, 0, 0] # Middle L, A, B values.
for i in range(200):
    img = sensor.snapshot()
    hist = img.get_histogram(roi=r)
    lo = hist.get_percentile(0.01) # Get the CDF of the histogram at the 1% range (ADJUST AS NECESSARY)!
    hi = hist.get_percentile(0.99) # Get the CDF of the histogram at the 99% range (ADJUST AS NECESSARY)!
    # Average in percentile values.
    threshold[0] = (threshold[0] + lo.l_value()) // 2
    threshold[1] = (threshold[1] + hi.l_value()) // 2
    threshold[2] = (threshold[2] + lo.a_value()) // 2
    threshold[3] = (threshold[3] + hi.a_value()) // 2
    threshold[4] = (threshold[4] + lo.b_value()) // 2
    threshold[5] = (threshold[5] + hi.b_value()) // 2
    for blob in img.find_blobs([threshold], pixels_threshold=200, area_threshold=100, merge=True, margin=10):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())
        img.draw_rectangle(r)

#print("Thresholds learned...")
#print("Tracking colors...")
print(threshold);"""
print(sensor.get_rgb_gain_db())
print(sensor.get_gain_db())
threshold= [43, 76, 32, 77, -5, 63]

d=0
while(True):
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs([threshold], pixels_threshold=100, area_threshold=100, merge=True, margin=10):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())

        angle= int(blob.cx()*.40625)
        #print(angle-70)
        uart.writechar(angle)
        #time.sleep(1)

        #uart.writechar(blob.rect()[2])
        #print(blob.cx())
        #print(blob.cx(), blob.cy(), blob.rect())
        #print(blob.rect()[2])
    ##print(clock.fps())
