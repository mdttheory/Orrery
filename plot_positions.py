import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
f = open("data/raw_positions.txt")

i = 1
data = []
for line in f:
	data_aux = []
	for x in line.split(","):
		data_aux.append(float(x))
	data.append(data_aux)

for point in data:
	ax.scatter(point[0], point[1], point[2])

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show()

