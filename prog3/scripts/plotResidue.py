import matplotlib.pyplot as plt
import numpy as np

data = []
with open("../data/data.csv", "r") as f:
	for line in f:
		data.append(line[:-1].split(","))

x = []
y = []
shift = {0:0, 1:1, 3:2, 5:3, 7:4, 2:5, 4:6, 6:7, 8:8}
labels = ['KK', 'R (S)', 'R (P)', 'RR (S)', 'RR (P)', 'HC (S)','HC (P)','SA (S)','SA (P)']
colors = []
for i in xrange(len(data)):
	for j in xrange(len(data[i])):
		x.append(shift[j])
		y.append(int(data[i][j]))
		if shift[j] in [0]:
			colors.append("red")
		elif shift[j] in [1, 2, 3, 4]:
			colors.append("blue")
		elif shift[j] in [5, 6, 7, 8]:
			colors.append("green")

x = np.array(x)
y = np.array(y)

splt = plt.subplot(1,1,1)
splt.set_xlabel('Heuristics')
splt.set_ylabel('Residue')
plt.scatter(x, y, color=colors)
plt.xticks(x, labels)
plt.ylim([1,100000000000000])
plt.yscale('log')
plt.savefig('../img/residues.png')
plt.show()