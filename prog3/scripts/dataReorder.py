data = []
with open("../data/times.csv", "r") as f:
	for line in f:
		data.append(line[:-1].split(","))

shift = {0:0, 1:1, 3:2, 5:3, 7:4, 2:5, 4:6, 6:7, 8:8}

for i in xrange(len(data)):
	row = data[i]	
	newRow = [0] * 9
	for j in xrange(9):
		newRow[shift[j]] = row[j]
	data[i] = newRow

with open("../data/timesReordered.csv", "w") as f:
	for datum in data:
		f.write(" & ".join(datum) + "\\\\\n")