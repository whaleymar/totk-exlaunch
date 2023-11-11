#!/bin/python3

import argparse

def readFilterFile(filterFile):
    with open(filterFile, 'r') as f:
        symList = f.readlines()
    return set([sym.strip() for sym in symList])

def filterSyms(symFile, symList):
    newLines = []
    with open(symFile, 'r') as f:
        for line in f.readlines():
            sym = line.split(' ')[0].strip()
            # print(sym)
            if sym in symList:
                newLines.append(line)
    # print(newLines)
    return newLines

def saveFilteredSyms(filteredSyms, destFile):
    with open(destFile, 'w') as f:
        f.writelines(filteredSyms)

def main(filterFile, symFile, destFile):
    symList = readFilterFile(filterFile)
    filteredSyms = filterSyms(symFile, symList)
    saveFilteredSyms(filteredSyms, destFile)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='filter sym file based on list')
    parser.add_argument('neededSyms', help='relative path to file of needed symbols')
    parser.add_argument('symFile', help='relative path to file all symbols')
    parser.add_argument('destFile', help='relative path to save new symbol file')

    args = parser.parse_args()
    main(args.neededSyms, args.symFile, args.destFile)