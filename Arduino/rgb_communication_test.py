from serial import Serial
import time

ser = Serial("/dev/cu.wchusbserial1420", 9600, timeout=1.0)

start_time = time.time()
for i in range(255):
    print("iteration: {}".format(i))
    # Set the color and show it
    ser.write([0xA0, i])
    ser.write([0xA1, 255 - i])
    ser.write([0xA2, i])
    # brightness
    ser.write([0xA3, 0xFF])
    # and show it
    ser.write([0xA4, 0x00])
    print(ser.read())
print time.time() - start_time

ser.close()
