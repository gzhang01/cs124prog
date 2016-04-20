import matplotlib.pyplot as plt
import numpy as np

data = []
with open("../data/times.csv", "r") as f:
	for line in f:
		data.append(line[:-1].split(","))

x = []
y = []
shift = {0:-1, 1:-1, 3:0, 5:1, 7:2, 2:-1, 4:3, 6:4, 8:5}
labels = ['RR (S)', 'RR (P)', 'HC (S)','HC (P)','SA (S)','SA (P)']
colors = []
for i in xrange(len(data)):
	for j in xrange(len(data[i])):
		if j in [0, 1, 2]:
			continue
		assert(shift[j] != -1)
		x.append(shift[j])
		y.append(int(data[i][j]))
		if shift[j] in [0, 1, 2]:
			colors.append("blue")
		elif shift[j] in [3, 4, 5]:
			colors.append("green")

x = np.array(x)
y = np.array(y)

splt = plt.subplot(1,1,1)
splt.set_xlabel('Heuristic')
splt.set_ylabel('Time (in ms)')
plt.scatter(x, y, color=colors)
plt.xticks(x, labels)
plt.ylim([10,2500])
plt.yscale('log')
plt.savefig('../img/times.png')
plt.show()