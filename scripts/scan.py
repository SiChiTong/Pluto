#!/usr/bin/python

import glob
import rlcompleter, readline
import code
import time
import serial
import sys

class Scan:
    '''
    Scans all the connected subsystems.
    '''
    def __init__(self):
        self.valids = []
        self.subsysName = []
        self.baseAddr = "/dev/ttyUSB*"

    def show(self):
        '''
        Prints all the valid subsystem ports.
        '''
        self.valids = glob.glob(self.baseAddr)
        self.subsysName = [0] * len(self.valids)
        print self.valids

    def listPorts(self):
        '''
        Returns a list of all valid subsytem ports.
        '''
        self.valids = glob.glob(self.baseAddr)
        return self.valids

    def assign(self):
        '''
        Querys all the connected subsystems and maps
        their names with their ports
        '''
        subsysNum = 0
        for v in self.valids:
            ser=serial.Serial(port=v,baudrate=115200)
            if False==ser.isOpen():
                ser.open()
            resp = []
            t_end=time.time()+10
            while time.time()<t_end:
                if ser.inWaiting()>0:
                    ser.write("v")
                    l = ser.readline()
                    if "Name:" in l:
                        self.subsysName[subsysNum]=l
                        break
            ser.close()
            subsysNum = subsysNum+1

    def showMap(self):
        for i in range( 0, len(self.valids) ):
            print "Port: ", self.valids[i], "===>", self.subsysName[i]
 
    def getNames(self):
        '''
        Returns a list of subsystem names, list index can be used
        to find their port number from listValids()
        '''
        return self.subsysName
 
def main():

    s=Scan()
    s.show()
    s.assign()
    s.showMap()

    if( "-i" in sys.argv ):
        readline.parse_and_bind('tab: complete')
        vars = globals().copy()
        vars.update(locals())
        shell = code.InteractiveConsole(vars)
        shell.interact()

if __name__ == "__main__":
    main()
