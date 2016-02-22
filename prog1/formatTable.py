rows = []

with open("data/output.csv") as f:
	rows = f.readlines()

for i in xrange(len(rows)):
	rows[i] = rows[i][:-1]
	rows[i] = rows[i].split(",")

new_rows = []
new_rows.append(["n", "trials", "d = 0", "d = 2", "d = 3", "d = 4"])
rows.pop(0)

count = 1
last = '1'
for row in rows:
	if row[1] == '0':
		new_rows.append([row[0], row[2], row[3]])
	else:
		if last != row[1]:
			last = row[1]
			count = 1
		new_rows[count].append(row[3])
		count += 1

for i in xrange(len(new_rows)):
	new_rows[i] = "&".join(new_rows[i]) + "\\\\\n"
	with open("data/finalResults.csv", "a") as f:
		f.write(new_rows[i])