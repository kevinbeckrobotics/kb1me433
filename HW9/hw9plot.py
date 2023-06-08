import csv
import matplotlib.pyplot as plt
import numpy as np

#create arrays for sig A
tA = []
dataA = []

#open sig A

with open('sigA.csv') as sigA:
    reader = csv.reader(sigA)
    for row in reader:
        tA.append(float(row[0]))
        dataA.append(float(row[1]))

#Fourier and plot A

FsA = 10000
TsA = 1/FsA
ts = np.arange(0, tA[-1], TsA)
yA = dataA
nA = len(dataA)
kA = np.arange(nA)
TA = nA/FsA
frqA = kA/TA # two sides frequency range
frqA = frqA[range(int(nA/2))] # one side frequency range
YA = np.fft.fft(yA)/nA # fft computing and normalization
YA = YA[range(int(nA/2))]

#create arrays for sig B
tB = []
dataB = []

#open sig B

with open('sigB.csv') as sigB:
    reader = csv.reader(sigB)
    for row in reader:
        tB.append(float(row[0]))
        dataB.append(float(row[1]))

#Fourier and plot B

FsB = 10000
TsB = 1/FsB
ts = np.arange(0, tB[-1], TsB)
yB = dataB
nB = len(dataB)
kB = np.arange(nB)
TB = nB/FsB
frqB = kB/TB # two sides frequency range
frqB = frqB[range(int(nB/2))] # one side frequency range
YB = np.fft.fft(yB)/nB # fft computing and normalization
YB = YB[range(int(nB/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(tA,yA,'b')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frqA,abs(YA),'b') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.show()

plt.figure(1)

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(tB,yB,'b')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frqB,abs(YB),'b') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.show()

plt.figure(2)

#create arrays for sig C
tC = []
dataC = []

#open sig C

with open('sigC.csv') as sigC:
    reader = csv.reader(sigC)
    for row in reader:
        tC.append(float(row[0]))
        dataC.append(float(row[1]))

#Fourier and plot C

FsC = 10000
TsC = 1/FsC
ts = np.arange(0, tC[-1], TsC)
yC = dataC
nC = len(dataC)
kC = np.arange(nC)
TC = nC/FsC
frqC = kC/TC # two sides frequency range
frqC = frqC[range(int(nC/2))] # one side frequency range
YC = np.fft.fft(yC)/nC # fft computing and normalization
YC = YC[range(int(nC/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(tC,yC,'b')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frqC,abs(YC),'b') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.show()
plt.figure(3)

#create arrays for sig D
tD = []
dataD = []

#open sig D

with open('sigD.csv') as sigD:
    reader = csv.reader(sigD)
    for row in reader:
        tD.append(float(row[0]))
        dataD.append(float(row[1]))

#Fourier and plot D

FsD = 10000
TsD = 1/FsD
ts = np.arange(0, tD[-1], TsD)
yD = dataD
nD = len(dataD)
kD = np.arange(nD)
TD = nD/FsD
frqD = kD/TD # two sides frequency range
frqD = frqD[range(int(nD/2))] # one side frequency range
YD = np.fft.fft(yD)/nD # fft computing and normalization
YD = YD[range(int(nD/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(tD,yD,'b')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frqD,abs(YD),'b') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.show()
plt.figure(4)

