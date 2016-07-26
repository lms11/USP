from __future__ import print_function
import sys
import random

if __name__ == "__main__":
	if len(sys.argv) != 3:
		print("Usage: spark_mlib <input> <features>", file=sys.stderr)
		exit(-1)

	# Number of inputs/lines
	inputs = int(sys.argv[1])

	# Number of features
	features = int(sys.argv[2])

	for x in range(0, inputs):
		category = random.randint(0, 1)
		print(category, end="")

		for y in range(0, features):
			feature_value = random.randint(0, 100)
			print(" %d" % (feature_value), end="")

		print("")
