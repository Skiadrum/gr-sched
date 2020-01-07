#!/usr/bin/env python3

import pandas as pd
import numpy as np
import scipy.stats
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import axes3d, Axes3D

# plt.style.use('grcon.mplrc')

my_colors = plt.rcParams['axes.prop_cycle'].by_key()['color']


def conf_int(data, confidence=0.95):
    a = 1.0 * np.array(data)
    n = len(a)
    m, se = np.mean(a), scipy.stats.sem(a)
    if (n < 2) or (se == 0):
        return np.nan
    h = se * scipy.stats.t.ppf((1 + confidence) / 2., n - 1)
    return h


################################################################
## Line Plot RT-Prio (n, n) scaling
################################################################
d = pd.read_csv('../perf-data/msg.csv')
d = d[d['config'] == 'fork']

t = d.groupby(['prio', 'burst_size', 'stages']).agg({'time': [np.mean,
                                                              np.var]}).reset_index()
print(t)
# t = t.groupby(['prio', 'burst_size'])
t = t.pivot('stages', 'prio', ('time', 'mean'))

fig, ax = plt.subplots(1, 1)

for c in t.columns:
    plt.plot(t[c].index, t[c], label=str(c))

ax.set_xlabel('\#\,Pipes $\\times$ \#\,Stages')
ax.set_ylabel('Time (in ms)')

ax.legend(title='Burst Size', handlelength=2.95)
fig.savefig('rt-buf.pdf')
plt.show()