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
d = (pd.read_csv('../perf-data/dur.csv'))


d.set_index("pipes", inplace= True)

#fig.savefig('dur-violin.pdf')


# Create the violineplot



pos = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
fig, axes = plt.subplots(1, 1)

test = [d.loc[1]['time'],d.loc[2]['time'],d.loc[3]['time'],d.loc[4]['time'],d.loc[5]['time'],
        d.loc[6]['time'],d.loc[7]['time'],d.loc[8]['time'],d.loc[9]['time'],d.loc[10]['time']]

print(d.groupby('run')['time'].count())
t = d.groupby('run').count()
print(t['time'])
axes.bar(pos, test)

axes.set_xlabel('Number of Runs')
axes.set_ylabel('Number of Timestamps')

fig.suptitle("Bar Plot")
#fig.subplots_adjust(hspace=0.4)
plt.show()

#fig.savefig('dur-violin.pdf')
