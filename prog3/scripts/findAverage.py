data = []
with open("../data/timesReordered.csv", "r") as f:
	for line in f:
		data.append(line[:-3].split(" & "))

sumData = [0] * 9
for datum in data:
	for i in xrange(9):
		sumData[i] += int(datum[i])

for i in xrange(9):
	sumData[i] /= len(data)

print sumData