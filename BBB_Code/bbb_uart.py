import serial
import Adafruit_BBIO.UART as UART
import time
UART.setup("UART4")
ser = serial.Serial("/dev/ttyO4", timeout=None, baudrate=115200) # open serial port
ser.close()
ser.open()

data = "hello Tiva. This is a message from Beaglebone"

# do I need to add a loop? what would the condition to stop be? use while True:?
try:
    if ser.isOpen():
        result = None
        print("Serial is open")
        ser.write(data.encode('utf-8'))
    ser.close()


except KeyboardInterrupt:
    # close serial port when ctrl-c is pressed
    ser.close()
    print("serial port closed")
