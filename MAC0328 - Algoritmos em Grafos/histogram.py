import numpy as np
import matplotlib.pyplot as plt
from sys import stdin

x = []
y = []
i = 0

for line in stdin:
    x.append(i)
    y.append(int(line))
    i = i + 1

print (np.mean(x))
print (np.std(x))

pos = np.arange(len(x))
width = 1.0     # gives histogram aspect to the bar diagram

plt.bar(pos, y, width)
plt.show()
