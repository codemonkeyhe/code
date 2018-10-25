#!/usr/bin/env python
# Filename: finally.py
import os
import time
import sys

try:
	#f=file('poem.txt')
	f=open('poem.txt')
	while True: # our usual file-reading idiom
		line=f.readline()
		if len(line)==0:
			break
		time.sleep(2)
		print (line,)
finally:
	f.close()
	print ('Cleaning up...closed the file')

