#!/usr/bin/env python
import os, sys, subprocess, time
import filecmp as fc

# --------------------------------------------------------------------------------------------------------
# Backport of Python 2.7's subprocess.check_output function from https://gist.github.com/edufelipe/1027906
def check_output(*popenargs, **kwargs):
    r"""Run command with arguments and return its output as a byte string.

    Backported from Python 2.7 as it's implemented as pure python on stdlib.

    >>> check_output(['/usr/bin/python', '--version'])
    Python 2.6.2
    """
    process = subprocess.Popen(stdout=subprocess.PIPE, *popenargs, **kwargs)
    output, unused_err = process.communicate()
    retcode = process.poll()
    if retcode:
        cmd = kwargs.get("args")
        if cmd is None:
            cmd = popenargs[0]
        error = subprocess.CalledProcessError(retcode, cmd)
        error.output = output
        raise error
    return output
# -------------------------------------------------------------------------------------------------------- 
 
# Get the total number of args passed to the demo.py
argc = len(sys.argv)
usage = "   Usage: ./tester-pa3.py <testsDirectoryName>"
 
# Check if correct number of args where given
if argc != 2:
    print "Must enter directory name containing test files."
    print usage
    sys.exit()
 
# Get the arguments list
cmdargs = str(sys.argv[1])
 
testDir = "./" + cmdargs
testFile = cmdargs
 
# Clearing and opening log file
open('pa3-tester-log', 'w').close()
testLog = open('pa3-tester-log', 'a')
 
# Used in the end to print the ugly 'failed' message
didFail = False
 
print "     ------------------------------------------"
print "     | Welcome to Antriksh and Kyly's tester! |"
print "     ------------------------------------------"
print ""
 
try:
    subprocess.check_call(['make'])
except subprocess.CalledProcessError:
    print "Could not 'make' for some reason. Exiting..."
    sys.exit()
 
print ""
 
# Error checking for missing directory etc.
try:
    if os.listdir(testDir) == []:
        print testDir + " is empty. Add some sample input files to it.\n"
        sys.exit()
 
except OSError:
    print "Do you have a directory called "+ testDir + "?"
    print "If not, make one and put sample input files in it.\n"
    sys.exit()
 
failList = []
# Loops through all testcases
for testFileName in os.listdir( testDir ):
    testFilePath = os.path.join( testFile, testFileName)
 
    # Tests user's program
    print "Testing " + testFileName + " on ./netplan..."
    start = time.time()
    uOut = check_output(['./netplan', testFilePath])
    userTime = time.time() - start
    print "Running time: %.3f sec" % userTime
 
    # Tests reference program
    print "Testing " + testFileName + " on ./refnetplan..."
    start = time.time()
    rOut = check_output(['./refnetplan', testFilePath])
    refTime = time.time() - start
    print "Running time: %.3f sec" % refTime
 
    # Prints time difference
    print "Time difference (your time - ref time): %.3f" % (userTime - refTime)
 
    testLog.write('---------------------------------\n\n')
 
 
    # Conclusion for current test (to stdout and log)
    if uOut == rOut:
        testLog.write('PASS: ' + testFileName + '\nTime difference: ' + str(userTime - refTime) + '\n')
        print "Test passed.\n"
    else:
        testLog.write('FAIL: ' + testFileName + '\n')
        didFail = True
        failList.append( testFileName )
        print "Test failed.\n"
 
    # Write outputs to log
    testLog.write('\nUser output:\n')
    testLog.write(uOut)
    testLog.write('\nRef output:\n')
    testLog.write(rOut)
    testLog.write('---------------------------------\n\n')
 
# Prints fail/success messages
if didFail:
    print "%d test cases failed. Test log saved in 'pa3-tester-log'." % len(failList)
    print ""
    print "Test case(s) that failed: "
    for failed in failList:
        print "     " + failed
    print ""
    print "Keep in mind that you do not have to account for disconnected graphs."
    print "In case of ties for lowest edge weights, any one of the possible MSTs will be accepted.\n"
else:
    print "All tests passed. You rock! Test log saved in 'pa3-tester-log'.\n"

print "Any negative time differences mean your netplan was faster than refnetplan.\n"

testLog.write('\n')
testLog.close()
 
sys.exit()