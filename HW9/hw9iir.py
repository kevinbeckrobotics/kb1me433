import csv
import matplotlib.pyplot as plt
import numpy as np

#create arrays for sig A
AA = 0.9991
BA = 1 - AA

tA = []
dataA = []
iirA = []
active = 0

#open sig A

with open('sigA.csv') as sigA:
    reader = csv.reader(sigA)
    for row in reader:
        tA.append(float(row[0]))
        dataA.append(float(row[1]))
        if active == 0:
            iirA.append(float(dataA[active]))
        else:
            iirA.append(AA * iirA[active - 1] + BA * dataA[active])
        active = active + 1
#Fourier and plot A

plt.plot(tA,dataA,'b')
plt.plot(tA,iirA,'r')
plt.xlabel('time')
plt.ylabel('amplitude')
plt.show()

#create arrays for sig B
AB = 0.9997
BB = 1 - AB

tB = []
dataB = []
iirB = []
active = 0

#open sig A

with open('sigB.csv') as sigB:
    reader = csv.reader(sigB)
    for row in reader:
        tB.append(float(row[0]))
        dataB.append(float(row[1]))
        if active == 0:
            iirB.append(float(dataB[active]))
        else:
            iirB.append(AB * iirB[active - 1] + BB * dataB[active])
        active = active + 1
#Fourier and plot A

plt.plot(tB,dataB,'b')
plt.plot(tB,iirB,'r')
plt.xlabel('time')
plt.ylabel('amplitude')
plt.show()

#create arrays for sig B
AC = 0.4
BC = 1 - AC

tC = []
dataC = []
iirC = []
active = 0

#open sig A

with open('sigC.csv') as sigC:
    reader = csv.reader(sigC)
    for row in reader:
        tC.append(float(row[0]))
        dataC.append(float(row[1]))
        if active == 0:
            iirC.append(float(dataC[active]))
        else:
            iirC.append(AC * iirC[active - 1] + BC * dataC[active])
        active = active + 1
#Fourier and plot A

plt.plot(tC,dataC,'b')
plt.plot(tC,iirC,'r')
plt.xlabel('time')
plt.ylabel('amplitude')
plt.show()

