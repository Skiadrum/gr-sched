#!/usr/bin/env python3

import pandas as pd
import numpy as np
import scipy.stats
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import axes3d, Axes3D
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
d = pd.read_csv('../perf-data/buf.csv')
d = d[d['config'] == 'fork']

t = d.groupby(['rt', 'stages']).agg({'time': [np.mean,
np.var]}).reset_index()
print(t)
t = t.pivot('stages', 'rt', ('time', 'mean'))
print(t)
fig, ax = plt.subplots(1, 1)

for c in t.columns:
    plt.plot(t[c].index**2, t[c], label=str(c))

ax.set_xlabel('Pipes and Stages')
ax.set_ylabel('Real (in s)')

ax.legend(title='Thread Priority')

fig.savefig('rt-msg.pdf')
plt.show()
