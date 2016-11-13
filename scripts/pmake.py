import argparse
import sys, os
from subprocess import call

print "\n"
print "----------------------------------------"
print "----------------------------------------"
print "----------------------------------------"
print "------Invoking Pluto Build System-------"
print "----------------------------------------"
print "----------------------------------------"
print "----------------------------------------"
print "\n"


#----------------------------------------
# Print current directory
#----------------------------------------
print "Current dir:",os.getcwd()
print "\n"


#----------------------------------------
# Check arguments
#----------------------------------------
if len(sys.argv) > 1:
    if sys.argv[1] == "clean":
        call(["python","pbuild","clean"])

if len(sys.argv) == 1:
    call(["python","pbuild"])
