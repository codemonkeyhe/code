#!/usr/bin/env python
# Filename: pickling.py
import sys
#import cPickle as p
import pickle as p

shoplistfile='shoplist.data'
# the name of the file where we will store the object

shoplist=['apple','mango','carrot']

# Write to the file
#f=file(shoplistfile,'w')
f=open(shoplistfile,'wb')
p.dump(shoplist,f) # dump the object to a file
f.close()

del shoplist # remove the shoplist

# Read back from the storage
#f=file(shoplistfile)
f=open(shoplistfile, "rb")
storedlist=p.load(f)
print (storedlist)

