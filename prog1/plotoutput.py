import numpy as np
import matplotlib.pyplot as plt
import sys

# Import CSV
file = "data/finalResults.csv"
csv = np.genfromtxt(file, delimiter="&")

# Separate data by dimension
d0 = csv[:,2]
d2 = csv[:,3]
d3 = csv[:,4]
d4 = csv[:,5]
ds = [d0, [], d2, d3, d4]

x = np.asarray(csv[:,0])

for d in xrange(5):
	if d == 1:
		continue
	# plt.plot(x, ds[d][:,3])
	plt.scatter(x, ds[d], 100)
	plt.show()

# Plot Dimension 0
# plt.figure(1)
# plt.plot(d0[:,0], d0[:,3], '.')
# plt.show()

from scipy.optimize import curve_fit

def fit_func(x,a,b,c):
    return a*x**b + c

params0 = curve_fit(fit_func, x, d0[:,3])
[a0, b0, c0] = params0[0]
# a0 = 19.0172521584 
# b0 = 0.0761892397838 
# c0 = -22.4122322355

plt.figure(1)
plt.plot(x, fit_func(x,a0,b0,c0))
plt.scatter(x,d0[:,3])
plt.show()

# Plot Dimension 2
# plt.figure(2)
# plt.plot(d2[:,0], d2[:,3], '.')

params2 = curve_fit(fit_func, x, d2[:,3])
[a2, b2, c2] = params2[0]
# a2 = 2.37581906081 
# b2 = 0.469370994834 
# c2 = 17.0804317712

plt.figure(2)
plt.plot(x, fit_func(x,a2,b2,c2))
plt.scatter(x,d2[:,3])
plt.show()

# Plot Dimension 3
# plt.figure(3)
# plt.plot(d3[:,0], d3[:,3], '.')

params3 = curve_fit(fit_func, x, d3[:,3])
[a3, b3, c3] = params3[0]
# a2 = 2.22730381196
# b2 = 0.635446728239 
# c2 = 442.716136741

plt.figure(3)
plt.plot(x, fit_func(x,a3,b3,c3))
plt.scatter(x,d3[:,3])
plt.show()

# Plot Dimension 4
# plt.figure(4)
# plt.plot(d4[:,0], d4[:,3], '.')

params4 = curve_fit(fit_func, x, d4[:,3])
[a4, b4, c4] = params4[0]
# a2 = 2.03071148747
# b2 = 0.733142562993
# c2 = 2995.5716482

plt.figure(4)
plt.plot(x, fit_func(x,a4,b4,c4))
plt.scatter(x,d4[:,3])
plt.show()