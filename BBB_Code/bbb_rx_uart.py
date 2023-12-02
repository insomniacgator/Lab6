
import serial
import sys
import Adafruit_BBIO.UART as UART
UART.setup("UART4")
ser = serial.Serial("/dev/ttyO4", timeout=None, baudrate=115200) # open serial port
ser.close()
ser.open()

data = None


try:
    if ser.isOpen():
        result = None
        print("Serial is open")
        while True:
            data = ser.read(1).decode('utf-8').strip()
            if data:
                #print(data)
                sys.stdout.write(data)
    ser.close()


except KeyboardInterrupt:
    # close serial port when ctrl-c is pressed
    ser.close()
    print("serial port closed")

