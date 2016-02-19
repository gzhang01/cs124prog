import numpy as np
import matplotlib.pyplot as plt
import sys

# Import CSV
file = "data/output.csv"
csv = np.genfromtxt(file, delimiter=",")

# Separate data by dimension
d0 = csv[1:14,:]
d2 = csv[14:27,:]
d3 = csv[27:40,:]
d4 = csv[40:,:]

plt.figure(1)
plt.plot(d0[:,0], d0[:,3], '.')
plt.figure(2)
plt.plot(d2[:,0], d2[:,3], '.')
plt.figure(3)
plt.plot(d3[:,0], d3[:,3], '.')
plt.figure(4)
plt.plot(d4[:,0], d4[:,3], '.')
plt.show()


new_d2 = d2