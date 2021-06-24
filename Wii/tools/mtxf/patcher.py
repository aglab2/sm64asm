import sys
import os
from os import listdir
from os.path import isfile, join

if len(sys.argv) < 3:
    sys.exit("Usage: ./patcher.py PATH ROM")
    
patchespath = sys.argv[1]
rompath = sys.argv[2]

def toInt(x):
    return int(x, 16)

with open(rompath, "rb+") as rom:
    patchnames = [f for f in listdir(patchespath) if isfile(join(patchespath, f))]
    patchnames.sort(key=toInt)
    for patchname in patchnames:
        offset = int(patchname, 16)
        print("Applying patch " + patchname)
        
        patchpath = join(patchespath, patchname)
        with open(patchpath, "rb") as patch:
            
            rom.seek(offset)
            rom.write(patch.read())

os.system('chksum64.exe "' + rompath + '"')