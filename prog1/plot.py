import numpy as np
import matplotlib.pyplot as plt
import sys

# Import CSV
file = "data/knt100avg_new.csv"
csv = np.genfromtxt(file, delimiter=",")

s = ""

for d in xrange(5):
	if d in [1, 2, 3, 0,]:
	# if d in [1]:
		continue

	d_csv = 1 if d == 0 else d
	numpoints = csv[1:,0]
	d0 = csv[1:,d_csv]

	# print numpoints
	# print d0

	d_tmp = d if (d != 0) else 1
	new_d0 = d0 ** (-1 * (d_tmp))

	# print numpoints
	# print d0
	# print new_d0

	# fit = np.polyfit(numpoints, new_d0 , 1)
	# print list(fit)
	### This fit data from form n^-d taken from data n = 10 to 10000
	fit = []
	multiplier = 0
	if (d == 0): 
		fit = [0.10523204120493665, 21.197763419973427]
		fit[1] -= 20
		multiplier = 2
		scalar = 0.005
	if (d == 2): 
		fit = [0.16517538261952885, 22.97229280304088]
		fit[1] -= 20
		multiplier = 1.2
		scalar = 0.1
	if (d == 3): 
		fit = [0.23458454621312719, 35.856196376448942]
		fit[1] -= 35
		multiplier = 1.2
		scalar = 0.035
	if (d == 4): 
		fit = [0.24600034088745676, 18.665592765194326]
		fit[1] -= 18
		multiplier = 1.2
		scalar = 0.04
	# multiplier = 1
	# scalar = 0
	fit_fn = np.poly1d(fit)
	# fit_fn is now a function which takes in x and returns an estimate for y

	xs = list(numpoints)
	xs.sort()
	xs = np.asarray(xs)

	first = [[], []]
	second = [[], []]
	third = [[], []]

	for i in xrange(len(numpoints)):
		if numpoints[i] < 500:
			first[0].append(numpoints[i])
			first[1].append(d0[i])
		elif numpoints[i] > 1000:
			third[0].append(numpoints[i])
			third[1].append(d0[i])
		else:
			second[0].append(numpoints[i])
			second[1].append(d0[i])

	first_s = first[0]
	first_s.sort()
	first_s = np.asarray(first_s)
	second_s = second[0]
	second_s.sort()
	second_s = np.asarray(second_s)
	third_s = third[0]
	third_s.sort()
	third_s = np.asarray(third_s)

	# plt.plot(numpoints, fit_fn(numpoints))
	# plt.scatter(numpoints, new_d0);
	# plt.show()

	plt.plot(xs, (multiplier * (fit_fn(xs) ** (-1.0 / d_tmp)) + scalar))
	plt.scatter(numpoints, d0)
	plt.show()

	plt.plot(first_s, (multiplier * (fit_fn(first_s) ** (-1.0 / d_tmp)) + scalar))
	plt.scatter(first[0], first[1])
	plt.show()

	plt.plot(second_s, (multiplier * (fit_fn(second_s) ** (-1.0 / d_tmp)) + scalar))
	plt.scatter(second[0], second[1])
	plt.show()

	plt.plot(third_s, (multiplier * (fit_fn(third_s) ** (-1.0 / d_tmp)) + scalar))
	plt.scatter(third[0], third[1])
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







