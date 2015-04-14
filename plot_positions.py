import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt



f = open("data/raw_positions.txt")


n = 0
data = [[]]
for line in f:
	if line != '-\n':
		data_aux = []
		for x in line.split(","):
			data_aux.append(float(x)/(10.0**12.0))
		data[-1].append(data_aux)

	else:
		n+=1
		data_aux = []
		data.append([])

for i in range(0,n):
	fig = plt.figure()
	ax = fig.add_subplot(111, projection='3d')
	for point in data[i]:
			ax.scatter(point[0], point[1], point[2])
	ax.set_xlabel('X (billion kilometers)')
	ax.set_ylabel('Y (billion kilometers)')
	ax.set_zlabel('Z (billion kilometers)')
	plt.xlim([-8,8])
	plt.ylim([-8,8])
	ax.set_zlim([-8,8])
	plt.title('Position at timestep '+str(i))
	print ('saving figure ',i)
	plt.savefig('images/PositionData'+str(i)+'.png', bbox_inches='tight')



