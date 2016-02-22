import numpy as np
import matplotlib.pyplot as plt
import sys

# Import CSV
file = "data/finalResults.csv"
csv = np.genfromtxt(file, delimiter="&")

# Sort csv 
csv = csv[csv[:,0].argsort()]

# Separate data by dimension
d0 = csv[:,2]
d2 = csv[:,3]
d3 = csv[:,4]
d4 = csv[:,5]
ds = [d0, [], d2, d3, d4]

x = np.asarray(csv[:,0])

# for d in xrange(5):
# 	if d == 1:
# 		continue
# 	# plt.plot(x, ds[d][:,3])
# 	plt.scatter(x, ds[d], 100)
# 	plt.show()

from scipy.optimize import curve_fit

# def fit_func(x,a,b,c):
#     return a*x**b + c

# # Fitting Dimension 2
# params2 = curve_fit(fit_func, x, ds[2])
# [a2, b2, c2] = params2[0]
# print "Dimension 2"
# print a2, b2, c2
# # a2 = 0.654348253219
# # b2 = 0.499068430367
# # c2 = 0.205424972377

# plt.figure(2)
# plt.plot(x, fit_func(x,a2,b2,c2))
# plt.scatter(x,ds[2])
# plt.show()

# # Fitting Dimension 3
# params3 = curve_fit(fit_func, x, ds[3])
# [a3, b3, c3] = params3[0]
# print "Dimension 3"
# print a3, b3, c3
# # a3 = 0.678033837293
# # b3 = 0.662929407821
# # c3 = 0.735449923079

# plt.figure(3)
# plt.plot(x, fit_func(x,a3,b3,c3))
# plt.scatter(x,ds[3])
# plt.show()

# # Fitting Dimension 4
# params4 = curve_fit(fit_func, x, ds[4])
# [a4, b4, c4] = params4[0]
# print "Dimension 4"
# print a4, b4, c4
# # a4 = 0.737807664062
# # b4 = 0.743943378049
# # c4 = 1.64307260612

# plt.figure(4)
# plt.plot(x, fit_func(x,a4,b4,c4))
# plt.scatter(x,ds[4])
# plt.show()

#####################################################################

# Looks like polynomial is to the power of (d-1)/d for d=2,3,4
def fit_func_2(x,a,c):
	return a*x**(1.0/2.0) + c

def fit_func_3(x,a,c):
	return a*x**(2.0/3.0) + c

def fit_func_4(x,a,c):
	return a*x**(3.0/4.0) + c

# Fitting Dimension 2
params2 = curve_fit(fit_func_2, x, ds[2])
[a2, c2] = params2[0]
print("Dimension 2 %.4f %.4f" %(a2,c2))
# a2 = 0.6477
# c2 = 0.2858

plt.figure(2)
plt.plot(x, fit_func_2(x,a2,c2))
plt.scatter(x,ds[2],100)
plt.show()

# Fitting Dimension 3
params3 = curve_fit(fit_func_3, x, ds[3])
[a3, c3] = params3[0]
print("Dimension 3 %.4f %.4f" %(a3,c3))
# a3 = 0.6510
# c3 = 1.9652

plt.figure(3)
plt.plot(x, fit_func_3(x,a3,c3))
plt.scatter(x,ds[3],100)
plt.show()

# Fitting Dimension 4
params4 = curve_fit(fit_func_4, x, ds[4])
[a4, c4] = params4[0]
print("Dimension 4 %.4f %.4f" %(a4,c4))
# a4 = 0.6907
# c4 = 5.9482

plt.figure(4)
plt.plot(x, fit_func_4(x,a4,c4))
plt.scatter(x,ds[4],100)
plt.show()

#####################################################################

# Avg Total Weight converges to 1.2 for dimension 0
plt.figure(1)
plt.plot([-10000, 70000], [1.2, 1.2])
plt.scatter(x,ds[0],100)
plt.xlim([-10000, 70000])
plt.ylim([0, 2])
plt.show()

#####################################################################

# Zoom in
plt.figure(4)
plt.plot(x[:10], fit_func_4(x,a4,c4)[:10])
plt.scatter(x[:10], ds[4][:10],100)
plt.show()