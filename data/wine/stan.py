# coding: utf-8

import csv
import sys

filename = sys.argv[1]
start = int(sys.argv[2])
end = int(sys.argv[3])

csvfile = file(filename, 'rb')
reader = csv.reader(csvfile)

maxval = [0]*(end-start+1)
minval = [9999]*(end-start+1)

for line in reader:
    for i in range(start,end):
        if(float(line[i]) > maxval[i-start]):
            maxval[i-start] = float(line[i])
        if(float(line[i]) < minval[i-start]):
            minval[i-start] = float(line[i])
print maxval
print minval
standfile = file("standard.csv", 'wb')
writer = csv.writer(standfile)
csvfile.close()

csvfile = file(filename,'rb')
reader = csv.reader(csvfile)

for line in reader:
    standline = []
    for i in range(0,start):
        standline.append(line[i])

    for i in range(start,end+1):
        standline.append((float(line[i])-minval[i-start])/(maxval[i-start]-minval[i-start]))

    for i in range(end+1,len(line)):
        standline.append(line[i])
    writer.writerow(standline)

standfile.close()
