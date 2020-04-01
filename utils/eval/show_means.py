#!/usr/bin/env python3


#libraries
import numpy as np
import matplotlib.pyplot as plt

# set width of bar
barWidth = 0.25

# set height of bar
bars1 = [120194.762821, 81953.6818963, 102233.682481, 154466.372215, 223932.036278,
         319938.602359, 446259.306647, 593075.45426, 756704.711577, 924394.632136]
bars2 = [71071.3729292, 152397.79544, 363843.679706, 626916.031816, 752131.750742,
         865295.311582, 1092327.4453, 1199878.22246, 1422749.41127, 1508888.68571]
bars3 = [55207.047149, 132182.693219, 303541.152807, 535708.498704, 945515.348728,
         1422131.9142, 1980172.09088, 2335282.36516, 1623575.31042, 1664955.21522]

# Set position of bar on X axis
r1 = np.arange(len(bars1))
r2 = [x + barWidth for x in r1]
r3 = [x + barWidth for x in r2]

# Make the plot
plt.bar(r1, bars1, color='#7f6d5f', width=barWidth, edgecolor='white', label='1PU')
plt.bar(r2, bars2, color='#557f2d', width=barWidth, edgecolor='white', label='2PU')
plt.bar(r3, bars3, color='#2d7f5e', width=barWidth, edgecolor='white', label='3PU')

# Add xticks on the middle of the group bars
plt.xlabel('means', fontweight='bold')
plt.xticks([r + barWidth for r in range(len(bars1))], ['1x1', '2x2', '3x3', '4x4', '5x5',
                                                       '6x6', '7x7', '8x8', '9x9', '10x10'])

# Create legend & Show graphic
plt.legend()
plt.show()
