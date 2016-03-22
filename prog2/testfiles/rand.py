import random
import sys

y = 2*16448*16448

with open("t16448.txt", "a") as myfile:
	for i in range(0,y):
		myfile.write("%i\n" % (random.randint(-1, 1)))