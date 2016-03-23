import locale
locale.setlocale(locale.LC_ALL, 'en_US')

tmultiple = 3
t = 3
n = 2
times = []

while t <= 24:
	while n <= 256:
		if n < t:
			times.append(n * n * (2 * n - 1))
		else:
			times.append(7 * times[-1] + 18 * (n / 2) ** 2)
		n *= 2
	for i in xrange(len(times)):
		times[i] = locale.format("%d", times[i], grouping=True)
	with open("analytical.csv", "a") as f:
		f.write(str(t) + " & " + " & ".join(times) + " \\\\\n")
	times = []
	t += tmultiple
	n = 2