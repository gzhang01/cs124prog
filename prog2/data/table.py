table = []

with open("T005-195/d400.csv", "r") as f:
	for line in f:
		table.append([line[:-1]])

with open("T190-400/d400.csv", "r") as f:
	for line in f:
		table.append([line[:-1]])

files = ["T005-195/d600.csv", "T190-400/d600.csv", "T005-195/d800.csv", "T190-400/d800.csv", "T005-195/d1000.csv", "T190-400/d1000.csv"]

count = 0
reset = False
for file in files:
	with open(file, "r") as f:
		for line in f:
			tmp = line.split(",")
			table[count].append(tmp[1][:-1])
			count += 1
	if reset:
		count = 0
	reset = not reset

with open("latexTable.csv", "w") as f: 
	for line in table:
		if ((int) (line[0].split(",")[0])) % 10 == 0:
			f.write(",".join(line).replace(",", " & ") + "\\\\\n")
			count = 0