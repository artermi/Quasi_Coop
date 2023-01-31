import sys
import os
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict



d_name = sys.argv[1]

for root,dirs,files in sorted(os.walk(d_name,topdown = False)):

	for name in sorted(files):
		if name.find('.dat') >= 0:
			# A_0100_b_0200_l_0100_m_0100_d_0100_r_0100.dat
			# 0123456789|123456789|123456789|123456789|
			a = float(name[ 2: 6])/100
			b = float(name[ 9:13])/100
			l = float(name[16:20])/100
			m = float(name[23:27])/100
			d = float(name[30:34])/100
			r = float(name[37:41])/100

			with open(os.path.join(root, name)) as file:
				for last_line in file:
					pass
				nmbs = last_line.split()

			print('({},{},{},{},{},{}) = ({},{},{})'.format(a,b,l,m,d,r,nmbs[1],nmbs[2],nmbs[3]))


