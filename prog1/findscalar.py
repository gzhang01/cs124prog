ratios = [[], [], [], [], []]

predData = []
maxData = []

with open("data/knt100maxpred.csv") as f:
	predData = f.readlines()

with open("data/knt100max.csv") as f:
	maxData = f.readlines()

predData.pop(0)
maxData.pop(0)

for i in xrange(len(predData)):
	predData[i] = predData[i][:-1]
	predData[i] = predData[i].split(',')
	predData[i][0] = int(predData[i][0])
	for j in xrange(1, len(predData[i])):
		predData[i][j] = float(predData[i][j])
for i in xrange(len(maxData)):
	maxData[i] = maxData[i][:-1]
	maxData[i] = maxData[i].split(',')
	maxData[i][0] = int(maxData[i][0])
	for j in xrange(1, len(maxData[i])):
		maxData[i][j] = float(maxData[i][j])

assert (len(predData) == len(maxData))

for i in xrange(len(predData)):
	assert (len(predData[i]) == len(maxData[i]))
	ratios[0].append(predData[i][0])
	for j in xrange(1, 5):
		ratios[j].append(maxData[i][j] / predData[i][j])

for i in xrange(len(ratios[0])):
	s = str(ratios[0][i]) + "   "
	for j in xrange(1, 5):
		s += str(ratios[j][i]) + "   "
	print s

for i in xrange(1, 5):
	print max(ratios[i])

# Dimension		Multiplier
# 	0				3
# 	2				2.5
#	3				2
# 	4				2

