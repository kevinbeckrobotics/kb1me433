import csv

t = []
data1 = [] # column 1
data2 = [] # column 2
active = 0

with open('sigB.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(active)) # leftmost column
        data1.append(float(row[0])) # second column
        data2.append(float(row[1])) # third column
        active = active + 1

for i in t:
    # print the data to verify it was read
    print(str(data1[int(i)]) + ", " + str(data2[int(i)]))

