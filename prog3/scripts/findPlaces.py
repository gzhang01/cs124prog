data = []
with open("../data/dataReordered.csv", "r") as f:
	for line in f:
		data.append(line[:-3].split(" & "))

sequencePlacing = [[0 for i in xrange(3)] for i in xrange(3)]
partitionPlace = [[0 for i in xrange(3)] for i in xrange(3)]

places = [sequencePlacing, partitionPlace]

for row in data:
	sequence = [int(row[2]), int(row[3]), int(row[4])]
	partition = [int(row[6]), int(row[7]), int(row[8])]

	datum = [sequence, partition]

	for i in xrange(len(datum)):
		nums = [0, 1, 2]
		ma = datum[i].index(max(datum[i]))
		mi = datum[i].index(min(datum[i]))
		nums.pop(nums.index(ma))
		nums.pop(nums.index(mi))
		se = nums[0]

		places[i][0][mi] += 1
		places[i][1][se] += 1
		places[i][2][ma] += 1

print places