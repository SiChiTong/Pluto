import time
import serial
import sys

if len(sys.argv) < 2:
    print "Usage: python testSerial.py /dev/ttyUSB0"
    sys.exit()

if sys.argv[1] != "/dev/ttyUSB0" and sys.argv[1] != "/dev/ttyUSB1":
    sys.exit()

ser = serial.Serial(
      port=sys.argv[1],
      baudrate=115200,
)

if ser.isOpen() == False:
    ser.open()

input=1
while 1:
    input=raw_input(">>")
    if input == 'exit':
        ser.close()
        exit()
    else:
        ser.write(input)
        out = ''
        while ser.inWaiting() > 0:
            out+=ser.read(1)

        if out != '':
            print ">>"+out
