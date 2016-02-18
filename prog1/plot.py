import numpy as np
import matplotlib.pyplot as plt
import sys

# Import CSV
file = "knt100max.csv"
csv = np.genfromtxt(file, delimiter=",")

s = ""

for d in xrange(5):
	if d == 1:
		continue

	d_csv = 1 if d == 0 else d
	numpoints = csv[1:,0]
	d0 = csv[1:,d_csv]

	# print numpoints
	# print d0

	new_d0 = d0 ** -1

	fit = []
	multiplier = 0
	if (d == 0): 
		fit = [0.16799676,2.93108083]
		multiplier = 3.5
	if (d == 2): 
		fit = [0.03520531,2.6599906]
		multiplier = 2.5
	if (d == 3): 
		fit = [0.01392143,2.03798067]
		multiplier = 2
	if (d == 4): 
		fit = [0.00761201,1.65815953]
		multiplier = 1.8
	fit_fn = np.poly1d(fit)
	# fit_fn is now a function which takes in x and returns an estimate for y


	# plt.plot(numpoints, fit_fn(numpoints))
	# plt.plot(numpoints, new_d0);
	plt.plot(numpoints, multiplier * (fit_fn(numpoints) ** -1))
	plt.plot(numpoints, d0)

	plt.show()

	if d == 0:
		plt.plot(numpoints[30:], multiplier * (fit_fn(numpoints[30:]) ** -1))
		plt.plot(numpoints[30:], d0[30:])

		plt.show()

# 	fit = list(fit)
# 	s += str(fit)[1:-2].replace(' ', '') + ";"

# with open("coeff.csv", "a") as f:
# 	f.write(s[:-1] + "\n")



# Dimension		Multiplier
# 	0				3.5
# 	2				2.5
#	3				2
# 	4				1.8







