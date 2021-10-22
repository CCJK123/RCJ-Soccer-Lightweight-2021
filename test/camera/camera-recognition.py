# Untitled - By: PorridgePi - 周四 十月 21 2021

import sensor, image, time
import math, pyb
from pyb import Pin

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)

clock = time.clock()


# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B
#Min, B Max)
#thresholds = [(34, 59, 22, 35, 39, 61),(71, 87, 4, 27, 38, 63),(55, 71, 8, 38, 20, 65)]
#thresholds = [(34, 87, 4, 38, 20, 65)]
thresholds = [(56, 128, 14, 31, 31, 66)]

sensor.set_auto_gain(False, gain_db=int(8)) # must be turned off for color tracking
sensor.set_auto_whitebal(False, rgb_gain_db=(-6, -4, 1.5)) # must be turned off for color tracking
#current_exposure_time_in_microseconds = sensor.get_exposure_us()
EXPOSURE_SCALE = 2.0
sensor.set_auto_exposure(False, \
    exposure_us = int(6576 * EXPOSURE_SCALE))

# Only blobs that with more pixels than "pixel_threshold"
#and more area than "area_threshold" are
# returned by "find_blobs" below. Change
#"pixels_threshold" and "area_threshold" if you change the
#camera resolution. "merge=True" must be set to merge
#overlapping color blobs for color codes.

#print(current_exposure_time_in_microseconds)
print(sensor.get_exposure_us())

while(True):
    clock.tick()
    img = sensor.snapshot()
    #print(clock.fps())
    #print(sensor.get_exposure_us())
    print(sensor.get_rgb_gain_db())
    blobs = img.find_blobs(thresholds, pixels_threshold=100, area_threshold=100, merge=True)

    #if blob.code() == 1: # r/g code == (1 << 1) | (1 << 0) 1==RED 2==GREEN
        #p = pyb.Pin("P0", pyb.Pin.OUT_PP)
        #p.high() # or p.value(1) to make the pin high (3.3V)
    #if blob.code() == 2: # r/g code == (1 << 1) | (1 << 0)
        #p = pyb.Pin("P0", pyb.Pin.OUT_PP)
        #p.low() # or p.value(0) to make the pin low (0V)

    for blob in blobs:
        img.draw_rectangle(blob.rect())


