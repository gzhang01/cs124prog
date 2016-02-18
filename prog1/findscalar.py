ratios = [[], [], [], [], []]

avgData = []
maxData = []

with open("data/knt100avg.csv") as f:
	avgData = f.readlines()

with open("data/knt100max.csv") as f:
	maxData = f.readlines()

avgData.pop(0)
maxData.pop(0)

for i in xrange(len(avgData)):
	avgData[i] = avgData[i][:-1]
	avgData[i] = avgData[i].split(',')
	avgData[i][0] = int(avgData[i][0])
	for j in xrange(1, len(avgData[i])):
		avgData[i][j] = float(avgData[i][j])
for i in xrange(len(maxData)):
	maxData[i] = maxData[i][:-1]
	maxData[i] = maxData[i].split(',')
	maxData[i][0] = int(maxData[i][0])
	for j in xrange(1, len(maxData[i])):
		maxData[i][j] = float(maxData[i][j])

assert (len(avgData) == len(maxData))

for i in xrange(len(avgData)):
	assert (len(avgData[i]) == len(maxData[i]))
	ratios[0].append(avgData[i][0])
	for j in xrange(1, 5):
		ratios[j].append(maxData[i][j] / avgData[i][j])

for i in xrange(len(ratios[0])):
	s = str(ratios[0][i]) + "   "
	for j in xrange(1, 5):
		s += str(ratios[j][i])[:6] + "   "
	print s

# Dimension		Multiplier
# 	0				3
# 	2				2.5
#	3				2
# 	4				2

