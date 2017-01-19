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


# Check if dir exist, else create new one
def makedir(p):
    if not os.path.exists(p):
        os.makedirs(p)

# Check if dir exist and delete it
def rmdir(p):
    if os.path.exists(p):
        os.rmdir(p)

#----------------------------------------
# Check arguments
#----------------------------------------
if len(sys.argv) > 1:
    proot = os.environ.get('PLUTO_ROOT')

    # Clean
    if sys.argv[1] == "clean":
        call(["python","pbuild","clean"])
        if None == proot:
            print "PLUTO_ROOT not set"
        else:
            rmdir(proot+'/deploy/'+'bin')
            rmdir(proot+'/deploy/'+'labs')
            rmdir(proot+'/deploy')

    # Deploy
    if sys.argv[1] == "deploy":
        # Create release filesystem

        if None == proot:
            print "PLUTO_ROOT not set"
        else:
            makedir(proot+'/deploy/'+'bin')
            makedir(proot+'/deploy/'+'labs')
            call(["python","pbuild","deploy"])

if len(sys.argv) == 1:

    # Build
    call(["python","pbuild"])
