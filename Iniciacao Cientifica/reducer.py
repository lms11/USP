#!/usr/bin/python
import sys

def main(args):
	counter = 0

	for line in sys.stdin:
		line = line.strip()

		try:
			count = int(line)
		except ValueError:
			continue    # ignore lines that are not formatted correctly

		counter += count

	print('%d' % (counter))

if __name__ == '__main__':
	main(sys.argv)
