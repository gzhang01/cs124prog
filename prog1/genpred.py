import numpy as np


lin_fns = []

for d in xrange(5):
	if d == 1:
		continue
	fit = []
	if (d == 0): 
		fit = [0.13374127083715834, 6.1684804907091539]
	if (d == 2): 
		fit = [0.017243763166416404, 4.0175175984670837]
	if (d == 3): 
		fit = [0.0054664079219238727, 2.6732089366215859]
	if (d == 4): 
		fit = [0.0026841794200285845, 2.0023055625711859]
	lin_fns.append(np.poly1d(fit))

maxData = []

with open("data/knt100max.csv") as f:
	maxData = f.readlines()

maxData.pop(0)

for i in xrange(len(maxData)):
	maxData[i] = maxData[i][:-1]
	maxData[i] = maxData[i].split(',')
	maxData[i][0] = int(maxData[i][0])
	for j in xrange(1, len(maxData[i])):
		maxData[i][j] = float(maxData[i][j])

# print maxData[0][0]
# print fns[0](maxData[0][0]) ** -1

fns = [
	lambda x: 3.0 * lin_fns[0](x) ** -1 + 0.02,
	lambda x: 2.0 * lin_fns[1](x) ** -1 + 0.05,
	lambda x: 1.5 * lin_fns[2](x) ** -1 + 0.1,
	lambda x: 1.2 * lin_fns[3](x) ** -1 + 0.15,
]

with open("data/knt100maxpred.csv", "w") as f:
	f.write("numpoints,d0,d2,d3,d4\n")

for i in xrange(len(maxData)):
	n = maxData[i][0]
	string = "{0},{1},{2},{3},{4}\n".format(n, fns[0](n) ** -1, fns[1](n) ** -1, fns[2](n) ** -1, fns[3](n) ** -1)
	with open("data/knt100maxpred.csv", "a") as f:
		f.write(string)