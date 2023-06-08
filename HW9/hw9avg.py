import csv
import matplotlib.pyplot as plt
import numpy as np
X = 400

#create arrays for sig A
tA = []
dataA = []
avgA = []
i = 0
sumAvgA = 0

#open sig A

with open('sigA.csv') as sigA:
  reader = csv.reader(sigA)
  for row in reader:
    tA.append(float(row[0]))
    dataA.append(float(row[1]))
    sumAvgA = 0
    if i >= X - 1:
      for j in range(X):
        sumAvgA = sumAvgA + dataA[i - X + j]
      avgA.append(float(sumAvgA/X))
    else:
      for j in range(i):
        sumAvgA = sumAvgA + dataA[j]
      avgA.append(float(sumAvgA/(i+1)))
    i = i + 1

#Fourier and plot A

FsA = 10000
TsA = 1/FsA
tsA = np.arange(0, tA[-1], TsA)
yA = avgA
nUnfilA = len(yA)
nA = len(avgA)
kUnfilA = np.arange(nUnfilA)
kA = np.arange(nA)
TUnfilA = nUnfilA/FsA
TA = nA/FsA
frqUnfilA = kUnfilA/TUnfilA
frqA = kA/TA # two sides frequency range
frqUnfilA = frqUnfilA[range(int(nUnfilA/2))]
frqA = frqA[range(int(nA/2))] # one side frequency range
YUnfilA = np.fft.fft(dataA)/nUnfilA
YA = np.fft.fft(yA)/nA # fft computing and normalization
YUnfilA = YUnfilA[range(int(nUnfilA/2))]
YA = YA[range(int(nA/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(tA,dataA, 'r')
ax1.plot(tA,yA,'b')
ax1.set_xlabel('time')
ax1.set_ylabel('amplitude')
ax2.loglog(frqUnfilA,abs(YUnfilA), 'r')
ax2.loglog(frqA,abs(YA),'b') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.show()
# Write your code here :-)
#create arrays for sig A
tB = []
dataB = []
avgB = []
i = 0
sumAvgB = 0

#open sig A

with open('sigB.csv') as sigB:
  reader = csv.reader(sigB)
  for row in reader:
    tB.append(float(row[0]))
    dataB.append(float(row[1]))
    sumAvgB = 0
    if i >= X - 1:
      for j in range(X):
        sumAvgB = sumAvgB + dataB[i - X + j]
      avgB.append(float(sumAvgB/X))
    else:
      for j in range(i):
        sumAvgB = sumAvgB + dataB[j]
      avgB.append(float(sumAvgB/(i+1)))
    i = i + 1

#Fourier and plot A

FsB = 10000
TsB = 1/FsB
tsB = np.arange(0, tB[-1], TsB)
yB = avgB
nUnfilB = len(yB)
nB = len(avgB)
kUnfilB = np.arange(nUnfilB)
kB = np.arange(nB)
TUnfilB = nUnfilB/FsB
TB = nB/FsA
frqUnfilB = kUnfilB/TUnfilB
frqB = kB/TB # two sides frequency range
frqUnfilB = frqUnfilB[range(int(nUnfilB/2))]
frqB = frqB[range(int(nB/2))] # one side frequency range
YUnfilB = np.fft.fft(dataB)/nUnfilB
YB = np.fft.fft(yB)/nB # fft computing and normalization
YUnfilB = YUnfilB[range(int(nUnfilB/2))]
YB = YB[range(int(nB/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(tB,dataB, 'r')
ax1.plot(tB,yB,'b')
ax1.set_xlabel('time')
ax1.set_ylabel('amplitude')
ax2.loglog(frqUnfilB,abs(YUnfilB), 'r')
ax2.loglog(frqB,abs(YB),'b') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.figure(2)
plt.show()

#create arrays for sig A
tC = []
dataC = []
avgC = []
i = 0
sumAvgC = 0

#open sig A

with open('sigC.csv') as sigC:
  reader = csv.reader(sigC)
  for row in reader:
    tC.append(float(row[0]))
    dataC.append(float(row[1]))
    sumAvgC = 0
    if i >= X - 1:
      for j in range(X):
        sumAvgC = sumAvgC + dataC[i - X + j]
      avgC.append(float(sumAvgC/X))
    else:
      for j in range(i):
        sumAvgC = sumAvgC + dataC[j]
      avgC.append(float(sumAvgC/(i+1)))
    i = i + 1

#Fourier and plot A

FsC = 10000
TsC = 1/FsC
tsC = np.arange(0, tC[-1], TsC)
yC = avgC
nUnfilC = len(yC)
nC = len(avgC)
kUnfilC = np.arange(nUnfilC)
kC = np.arange(nC)
TUnfilC = nUnfilC/FsC
TC = nC/FsA
frqUnfilC = kUnfilC/TUnfilC
frqC = kC/TC # two sides frequency range
frqUnfilC = frqUnfilC[range(int(nUnfilC/2))]
frqC = frqC[range(int(nC/2))] # one side frequency range
YUnfilC = np.fft.fft(dataC)/nUnfilC
YC = np.fft.fft(yC)/nC # fft computing and normalization
YUnfilC = YUnfilC[range(int(nUnfilC/2))]
YC = YC[range(int(nC/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(tC,dataC, 'r')
ax1.plot(tC,yC,'b')
ax1.set_xlabel('time')
ax1.set_ylabel('amplitude')
ax2.loglog(frqUnfilC,abs(YUnfilC), 'r')
ax2.loglog(frqC,abs(YC),'b') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.figure(3)
plt.show()

#create arrays for sig A
tD = []
dataD = []
avgD = []
i = 0
sumAvgD = 0

#open sig A

with open('sigD.csv') as sigD:
  reader = csv.reader(sigD)
  for row in reader:
    tD.append(float(row[0]))
    dataD.append(float(row[1]))
    sumAvgD = 0
    if i >= X - 1:
      for j in range(X):
        sumAvgD = sumAvgD + dataD[i - X + j]
      avgD.append(float(sumAvgD/X))
    else:
      for j in range(i):
        sumAvgD = sumAvgD + dataD[j]
      avgD.append(float(sumAvgD/(i+1)))
    i = i + 1

#Fourier and plot A

FsD = 10000
TsD = 1/FsD
tsD = np.arange(0, tD[-1], TsD)
yD = avgD
nUnfilD = len(yD)
nD = len(avgD)
kUnfilD = np.arange(nUnfilD)
kD = np.arange(nD)
TUnfilD = nUnfilD/FsD
TD = nD/FsA
frqUnfilD = kUnfilD/TUnfilD
frqD = kD/TD # two sides frequency range
frqUnfilD = frqUnfilD[range(int(nUnfilD/2))]
frqD = frqD[range(int(nD/2))] # one side frequency range
YUnfilD = np.fft.fft(dataD)/nUnfilD
YD = np.fft.fft(yD)/nD # fft computing and normalization
YUnfilD = YUnfilD[range(int(nUnfilD/2))]
YD = YD[range(int(nD/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(tD,dataD, 'r')
ax1.plot(tD,yD,'b')
ax1.set_xlabel('time')
ax1.set_ylabel('amplitude')
ax2.loglog(frqUnfilD,abs(YUnfilD), 'r')
ax2.loglog(frqD,abs(YD),'b') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.figure(4)
plt.show()

