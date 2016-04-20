import matplotlib.pyplot as plt
import numpy as np

file = "sap"

data = []
with open("../data/" + file + ".csv", "r") as f:
	for line in f:
		data.append(line[:-1].split(","))

x = []
bestResidue = []
sResidue = []
residue = []
for datum in data:
	x.append(datum[0])
	bestResidue.append(datum[1])
	sResidue.append(datum[2])
	residue.append(datum[3])

x = np.array(x)
bestResidue = np.array(bestResidue)
residue = np.array(residue)

splt = plt.subplot(1,1,1)
splt.set_xlabel('Iteration')
splt.set_ylabel('Residue')
plt.scatter(x, residue, color="blue")
plt.scatter(x, sResidue, color="red")
plt.scatter(x, bestResidue, color="green")
plt.ylim([10**0,10**14])
plt.yscale('log')
plt.savefig("../img/" + file + ".png")
plt.show()