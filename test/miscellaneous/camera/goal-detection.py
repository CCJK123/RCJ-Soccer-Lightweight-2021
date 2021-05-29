# Import modules
import sensor, image, time

sensor.reset()                      # Reset and initialize the sensor.
sensor.set_pixformat(sensor.RGB565) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.


    goals = img.find_blobs([(50, 90, -30, 10, -45, -5), (50, 90, -30, 10, 15, 55)])
    #print(goals)
    #print(len(goals))
    for i in range(len(goals)):
        #print(goals[i])
        #print(goals[i].rect())
        if goals[i].pixels() > 250:
            print(goals[i])
            img.draw_rectangle(goals[i].rect())


    print(clock.fps())              # Note: OpenMV Cam runs about half as fast when connected
                                    # to the IDE. The FPS should increase once disconnected.
