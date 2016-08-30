import time
import serial

ser = serial.Serial(
      port='/dev/ttyUSB1',
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
