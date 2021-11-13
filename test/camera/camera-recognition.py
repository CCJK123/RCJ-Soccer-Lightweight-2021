# Untitled - By: PorridgePi - 周四 十月 21 2021

import sensor, image, time
import math, pyb
from pyb import Pin

SKIP_FRAMES = 2000
GAIN = 0
WHITE_BALANCE = (-6, -4, 1.5)
EXPOSURE = 2.0

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
BLUE_THRESHOLDS = [(23, 39, -2, 16, -51, -29),(42, 61, -31, 22, -59, -32)]
YELLOW_THRESHOLDS = [(35, 61, -4, 28, 27, 59)]
ROBOT_THRESHOLDS = [(10, 30, -18, 7, -8, 7)]

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)

# config
sensor.skip_frames(time=SKIP_FRAMES)
sensor.set_auto_gain(False, gain_db=GAIN) # must be turned off for color tracking
sensor.set_auto_whitebal(False, rgb_gain_db=WHITE_BALANCE) # must be turned off for color tracking
sensor.set_auto_exposure(False, exposure_us = int(6576 * EXPOSURE))

clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()

    #print(clock.fps())
    #print(sensor.get_exposure_us())
    print(sensor.get_rgb_gain_db())

    blue_blobs = img.find_blobs(BLUE_THRESHOLDS, pixels_threshold=100, area_threshold=50, merge=True, margin=30)
    yellow_blobs = img.find_blobs(YELLOW_THRESHOLDS, pixels_threshold=100, area_threshold=50, merge=True, margin=30)
    robot_blobs = img.find_blobs(ROBOT_THRESHOLDS, roi=(30,40,260,155), pixels_threshold=300, area_threshold=300, merge=True)

    #if blob.code() == 1: # r/g code == (1 << 1) | (1 << 0) 1==RED 2==GREEN
        #p = pyb.Pin("P0", pyb.Pin.OUT_PP)
        #p.high() # or p.value(1) to make the pin high (3.3V)
    #if blob.code() == 2: # r/g code == (1 << 1) | (1 << 0)
        #p = pyb.Pin("P0", pyb.Pin.OUT_PP)
        #p.low() # or p.value(0) to make the pin low (0V)

    for blob in blue_blobs:
        img.draw_rectangle(blob.rect(),color=0x045F)
    for blob in yellow_blobs:
        img.draw_rectangle(blob.rect(),color=0xEFE0)
    for blob in robot_blobs:
        img.draw_rectangle(blob.rect())
        #img.draw_rectangle((0,40,320,155))
