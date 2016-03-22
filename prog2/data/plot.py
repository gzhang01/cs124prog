import matplotlib.pyplot as plt
import csv

dim = 800

filename = "d%i.csv" % (dim)

f = open(filename)
csv_f = csv.reader(f)

threshold = []
runtime = []

for row in csv_f:
	threshold.append(row[0])
	runtime.append(row[1])


plt.plot(threshold, runtime)

#plt.plot(volt16_20v, volt16_20i)


# plt.legend(loc='right')
# plt.ylim((0,.20))
# plt.xlim((0,12))
plt.xlabel('Threshold')
plt.ylabel('Runtime')
# plt.title('')
plt.grid(True)
plt.savefig("d%i" % (dim))
plt.show()