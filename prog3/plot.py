import matplotlib.pyplot as plt
import numpy as np

data = []
with open("data.csv", "r") as f:
	for line in f:
		data.append(line[:-1].split(","))

x = []
y = []
shift = {0:0, 1:1, 3:2, 5:3, 7:4, 2:5, 4:6, 6:7, 8:8}
labels = ['KK', 
	'R (S)', 
	'R (P)', 
	'RR (S)', 
	'RR (P)', 
	'HC (S)',
	'HC (P)',
	'SA (S)',
	'SA (P)']

for i in xrange(len(data)):
	for j in xrange(len(data[i])):
		x.append(shift[j])
		y.append(int(data[i][j]))

x = np.array(x)
y = np.array(y)

plt.subplot(1,1,1)
plt.scatter(x, y)
plt.xticks(x, labels)
plt.ylim([1,100000000000000])
plt.yscale('log')
plt.show()