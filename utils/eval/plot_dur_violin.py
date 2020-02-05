#!/usr/bin/env python3

import pandas as pd
import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import axes3d, Axes3D
import pylab as pl
#plt.style.use('grcon.mplrc')

my_colors = plt.rcParams['axes.prop_cycle'].by_key()['color']

def conf_int(data, confidence=0.95):
    a = 1.0*np.array(data)
    n = len(a)
    m, se = np.mean(a), scipy.stats.sem(a)
    if (n < 2) or (se == 0):
        return np.nan
    h = se * scipy.stats.t.ppf((1+confidence)/2., n-1)
    return h




################################################################
## Line Plot RT-Prio (n, n) scaling
################################################################
d = (pd.read_csv('../perf-data/dur.csv', usecols = ['time']))

print(d['time'])
fig, ax = plt.subplots(1, 1)

plt.xlabel('duration')
plt.ylabel('numbers')

#fig.savefig('dur-violin.pdf')

ax = fig.add_axes([0,0,1,1])

# Create the boxplot
bp = ax.violinplot(d['time'])

plt.show()
