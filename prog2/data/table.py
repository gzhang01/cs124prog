table = []

with open("d400.csv", "r") as f:
	for line in f:
		table.append([line[:-3]])

files = ["d600.csv", "d800.csv", "d1000.csv"]

count = 0
for file in files:
	with open(file, "r") as f:
		for line in f:
			tmp = line.split(",")
			tmp[1] = tmp[1][:-1]
			if tmp[1][-2:] == "00":
				tmp[1] = tmp[1][:-2]
			if len(tmp[1]) == 2:
				tmp[1] += ".0"
			while (table[count][0].split(",")[0] != tmp[0]):
				table[count].append("-")
				count += 1
			table[count].append(tmp[1])
			count += 1
	while (count != len(table)):
		table[count].append("-")
		count += 1
	count = 0

with open("latexTable.csv", "w") as f: 
	for line in table:
		if ((int) (line[0].split(",")[0])) % 10 == 0:
			f.write(",".join(line).replace(",", " & ") + "\\\\\n")