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

print(d)
fig, ax = plt.subplots(1, 1)


plt.hist(d['time'], bins=[1000000,1500000,2000000,2500000,3000000,3500000,4000000], rwidth= 0.9)
plt.xlabel('duration')
plt.ylabel('numbers')

fig.savefig('duration.pdf')
plt.show()
