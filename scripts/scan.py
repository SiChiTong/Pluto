#!/usr/bin/python

import glob
import rlcompleter, readline
import code
import time

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
            t_end=time.time()+5
            ser.write('v')
            while time.time()<t_end:
                if ser.isWaiting()>0:
                    resp.append(ser.readline())
            ser.close()
            for l in resp:
                if "Name:" in l: 
                    self.subsysName[subsysNum]=l
            subsysName+=1
            print resp
            
def main():
    readline.parse_and_bind('tab: complete')
    vars = globals().copy()
    vars.update(locals())
    shell = code.InteractiveConsole(vars)
    shell.interact()

if __name__ == "__main__":
    main()
