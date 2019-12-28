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
sensor.set_auto_gain(False,15.56504)
sensor.set_auto_whitebal(False,[-6.02073, -3.454361, -0.4176831])
clock = time.clock()
"""
r = [(300//2)-(50//2), (220//2)-(50//2), 80, 80]
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
d=0
R=3.25
M=0.2190625
while(True):
	clock.tick()
	img = sensor.snapshot()
	for blob in img.find_blobs([threshold], pixels_threshold=100, area_threshold=100, merge=True, margin=10):
		img.draw_rectangle(blob.rect())
		img.draw_cross(blob.cx(), blob.cy())
		angle= int(blob.cx()*.40625)
		uart.writechar(angle)
                d=R/math.tan((M*blob.w()/2)*math.pi/180.0)
        print(d)
