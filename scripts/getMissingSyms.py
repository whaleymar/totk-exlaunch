#!/bin/python3

import subprocess

errorMsg = "undefined reference to "
msgLen = len(errorMsg)

def parseLine(line):
    if errorMsg not in line:
        return ""
    startIx = line.find(errorMsg) + msgLen + 1
    return line[startIx:-1]

def getErrorString(outputString):
    startIx = outputString.find(errorMsg)
    endIx = outputString.find("error: ld returned 1 exit status")

    # assert startIx > outputString.find("Linking CXX Executable")
    assert endIx > 0

    return outputString[startIx:endIx]

def make():
    # subprocess.run(["make", "clean"])
    return subprocess.run(["make"], capture_output=True, text=True).stderr

def main(outputString):
    # print(outputString)
    try:
        errorString = getErrorString(outputString)
    except AssertionError:
        print("No linking errors")
        return

    missingSyms = []
    for line in errorString.split('\n'):
        sym = parseLine(line)
        if sym:
            missingSyms.append(sym)
    missingSyms = list(set(missingSyms))
    for sym in missingSyms:
        print(sym)

if __name__ == "__main__":
    
    main(make())
