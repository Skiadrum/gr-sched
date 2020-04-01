#!/usr/bin/env python3

import numpy as np
import pandas as pd
import scipy.stats
import matplotlib.pyplot as plt

plt.style.use('sig-alternate.mplrc')

my_colors = plt.rcParams['axes.prop_cycle'].by_key()['color']


def conf_int(data, confidence=0.99):
    a = 1.0 * np.array(data)
    n = len(a)
    m, se = np.mean(a), scipy.stats.sem(a)
    if (n < 2) or (se == 0):
        return np.nan
    h = se * scipy.stats.t.ppf((1 + confidence) / 2., n - 1)
    return h


##################################################################
d = (pd.read_csv('../perf-data/1_2_3PU-samples=100000000.csv'))
d['Core'] = '3r1'

e = (pd.read_csv('../perf-data/dur.csv'))
e['Core'] = '3r2'

f = (pd.read_csv('../perf-data/1PU-samples=100000000.csv'))
f['Core'] = '1'

g = (pd.read_csv('../perf-data/2_3PU-samples=100000000.csv'))
g['Core'] = '2'

h = (pd.read_csv('../perf-data/1_3PU-samples=100000000.csv'))
h['Core'] = '13'

d = pd.concat([d, e, g, h], axis=0)

d = d.groupby(['Core', 'stages']).agg({'time': [np.mean, np.var, conf_int]})
print(d)

fig, ax = plt.subplots(1, 1)
fig.subplots_adjust(bottom=.192, left=.11, top=.99, right=.97)

t = d.loc['13']
ax.errorbar(t.index ** 2, t[('time', 'mean')], yerr=t[('time', 'conf_int')], label='13 Core')
t = d.loc['2']
ax.errorbar(t.index ** 2, t[('time', 'mean')], yerr=t[('time', 'conf_int')], label='23 Core')
t = d.loc['3r1']
ax.errorbar(t.index ** 2, t[('time', 'mean')], yerr=t[('time', 'conf_int')], label='3 Core Run1')
t = d.loc['3r2']
ax.errorbar(t.index ** 2, t[('time', 'mean')], yerr=t[('time', 'conf_int')], label='3 Core Run2')

plt.setp(ax.get_yticklabels(), rotation=90, va="center")
ax.set_xlabel('\#\,Pipes $\\times$ \#\,Stages')
ax.set_ylabel(' Average Execution Time (in ns)')


handles, labels = ax.get_legend_handles_labels()
handles = [x[0] for x in handles]
ax.legend(handles, labels, handlelength=1)

# plt.savefig('buf.pdf')

plt.show()
