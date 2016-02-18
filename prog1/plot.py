import numpy as np
import matplotlib.pyplot as plt
import sys

# Import CSV
file = "data/knt100avg.csv"
csv = np.genfromtxt(file, delimiter=",")

s = ""

for d in xrange(5):
	if d in [1,]:
		continue

	d_csv = 1 if d == 0 else d
	numpoints = csv[1:,0]
	d0 = csv[1:,d_csv]

	# print numpoints
	# print d0

	new_d0 = d0 ** -1

	# print numpoints
	# print d0
	# print new_d0

	# fit = np.polyfit(numpoints, new_d0 , 1)
	# print list(fit)
	fit = []
	multiplier = 0
	if (d == 0): 
		fit = [0.13374127083715834, 6.1684804907091539]
		multiplier = 3
		scalar = 0
	if (d == 2): 
		fit = [0.017243763166416404, 4.0175175984670837]
		multiplier = 2
		scalar = 0.05
	if (d == 3): 
		fit = [0.0054664079219238727, 2.6732089366215859]
		multiplier = 1.5
		scalar = 0.10
	if (d == 4): 
		fit = [0.0026841794200285845, 2.0023055625711859]
		multiplier = 1.2
		scalar = 0.15
	# multiplier = 1
	fit_fn = np.poly1d(fit)
	# fit_fn is now a function which takes in x and returns an estimate for y

	xs = list(numpoints)
	xs.sort()
	xs = np.asarray(xs)

	# plt.plot(numpoints, fit_fn(numpoints))
	# plt.scatter(numpoints, new_d0);
	plt.plot(xs, multiplier * (fit_fn(xs) ** -1) + scalar)
	plt.scatter(numpoints, d0)

	plt.show()

	# if d == 0:
	# 	plt.plot(numpoints[30:], multiplier * (fit_fn(numpoints[30:]) ** -1))
	# 	plt.plot(numpoints[30:], d0[30:])

	# 	plt.show()

# 	fit = list(fit)
# 	s += str(fit)[1:-2].replace(' ', '') + ";"

# with open("coeff.csv", "a") as f:
# 	f.write(s[:-1] + "\n")



# Dimension		Multiplier
# 	0				3.5
# 	2				2.5
#	3				2
# 	4				1.8







