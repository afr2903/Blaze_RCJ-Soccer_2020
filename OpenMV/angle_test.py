import sensor, image
import time
from pyb import UART
import ustruct
import math
uart = UART(3, 19200, timeout_char=200)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 500)
#sensor.set_auto_gain(False) #7.04294  must be turned off for color tracking
sensor.set_auto_whitebal(False,[-6.02073, -3.454361, -0.4176831]) # must be turned off for color tracking
clock = time.clock()

"""r = [(300//2)-(50//2), (220//2)-(50//2), 80, 80]
for i in range(150):
    img = sensor.snapshot()
    img.draw_rectangle(r)
threshold = [50, 50, 0, 0, 0, 0]
for i in range(200):
    img = sensor.snapshot()
    hist = img.get_histogram(roi=r)
    lo = hist.get_percentile(0.01)
    hi = hist.get_percentile(0.99)
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
print(threshold);"""
print(sensor.get_rgb_gain_db())
print(sensor.get_gain_db())
threshold= [37, 76, 32, 77, -5, 63]
#blue [17, 30, -16, 23, -52, -15]
#yellow [47, 70, -51, -30, 26, 63]
R=3.25
M=0.19375
d=0
h=-6.5+13

A=C=0
B=5
a=b=c=0
angle=0

while(True):
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs([threshold], pixels_threshold=100, area_threshold=100, merge=True, margin=10):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())

        if(blob.cy()<120):
            try:
                a= int(blob.cx()*.23125)-35.4
                d= R/math.tan((M*blob.w()/2)*math.pi/180.0)
                C= math.sqrt( d**2-h**2 )
                A= math.sqrt( (B**2+C**2) - (2*B*C*math.cos(a*math.pi/180.0)) )
                c= math.sin(a*math.pi/180.0)*C / A
                angle= math.asin(c)*180/math.pi*1.35
                if(A<10 and abs(angle)<60):
                    angle = 0
            except:
                angle = 0
                A = 0
        else:
            angle = 0
            A = 0

        #img.draw_line(0, 120, 320, 120, color = (0, 255, 0), thickness = 2)
        uart.writechar( int(angle+120) )
        uart.writechar( int(A) )
        #print(angle, A, blob.cy())
#70.8°
